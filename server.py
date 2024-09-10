import argparse
from flask import Flask, make_response, send_from_directory
import os

app = Flask(__name__)


# Serve static files from the current directory
@app.route("/<path:filename>")
def serve_static_files(filename):
    return send_from_directory(os.getcwd(), filename)


# Serve test.html by default
@app.route("/")
def serve_index():
    response = make_response(send_from_directory(os.getcwd(), "test.html"))
    response.headers["Cross-Origin-Embedder-Policy"] = "require-corp"
    response.headers["Cross-Origin-Opener-Policy"] = "same-origin"
    return response


def main():
    parser = argparse.ArgumentParser(description="Run test server")
    parser.add_argument(
        "--port",
        type=int,
        default=8000,
        help="Port to run the server on (default: 8000)",
    )
    args = parser.parse_args()
    app.run(debug=True, port=args.port)


if __name__ == "__main__":
    main()
