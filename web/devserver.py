#!/usr/bin/env python3
"""Simple Python 3 web server that serves files based on the runfiles manifest."""

import os
import posixpath
import signal
import sys
import http.server
from types import FrameType
from typing import Optional, Type

from rules_python.python.runfiles import runfiles  # type: ignore  # pylint: disable=import-error

PORT = 8080


def _join(*args: str) -> str:
    return posixpath.join(*(comp.lstrip(posixpath.sep) for comp in args))


def _make_handler(base_path: str) -> Type[http.server.SimpleHTTPRequestHandler]:
    runfiles_inst = runfiles.Create()

    class _Handler(http.server.SimpleHTTPRequestHandler):
        def translate_path(self, path: str) -> str:
            rloc: Optional[str] = runfiles_inst.Rlocation(_join(base_path, path))
            if rloc is None:
                rloc = runfiles_inst.Rlocation(_join(base_path, path, "index.html"))

            self.log_message("Translate '%s' -> '%s'", path, rloc)
            if rloc is not None:
                return rloc

            # Arbitrary path that probably doesn't exist on disk
            return "__invalid"

    return _Handler


def _main() -> None:
    with http.server.ThreadingHTTPServer(
        ("", PORT), _make_handler("decomposer/web")
    ) as httpd:
        print("Serving from", os.getcwd())
        print(f"http://127.0.0.1:{PORT}")

        def sig_hdlr(_sig: int, _frame: Optional[FrameType]) -> None:
            httpd.server_close()
            sys.exit(0)

        signal.signal(signal.SIGINT, sig_hdlr)

        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            sys.exit(0)


if __name__ == "__main__":
    _main()
