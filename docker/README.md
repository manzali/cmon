### README

* `cd cmon/docker/`
* `docker build -t cmon/centos7 -f Dockerfile .`
* `docker run -t -i -v ${HOME}/cmon/:/cmon cmon/centos7`