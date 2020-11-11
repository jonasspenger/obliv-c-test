# Obliv-c Test

## Setup
* Manual setup:
  * Download obliv-c submodule `git submodule update --init --recursive` and install following instructions (Ubuntu) [https://github.com/samee/obliv-c](https://github.com/samee/obliv-c).
* Docker setup:
  * Build (this may take up to 1 hour):
  ```
  docker build \
    -t obliv-c-template \
    .;
  ```
  * Run:
  ```
  docker run \
    --rm \
    obliv-c-template;
  ```
  * Run and enter shell:
  ```
  docker run \
    -it \
    --rm \
    obliv-c-template \
    /bin/bash;
  ```
  * Run and enter shell mounting this current directory (not safe, only for development):
  ```
  docker run \
    -v $(pwd)/src:/app/src \
    -it \
    --rm \
    obliv-c-template \
    /bin/bash;
  ```

## Projects
* [src/map](src/map)
  * Implementation of a (stateful) secure map, with operators get, set, remove, clear, prune.
