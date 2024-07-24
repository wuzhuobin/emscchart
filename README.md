# EMSCCHART


## Prerequsite

* [vscode](https://code.visualstudio.com/)
* [devcontainer](https://code.visualstudio.com/docs/devcontainers/containers)
* [docker](https://www.docker.com/get-started/)
* [docker proxy](https://docs.docker.com/network/proxy/)
    * Append below script in your host `~/.bashrc`
        ```bash
        export http_proxy=XXXXXXXXXXXX
        export HTTP_PROXY=XXXXXXXXXXXX
        export https_proxy=XXXXXXXXXXXX
        export HTTPS_PROXY=XXXXXXXXXXXX
        export FTP_PROXY=XXXXXXXXXXXX
        export ftp_proxy=XXXXXXXXXXXX
        export no_proxy=127.0.0.1,localhost,XXXXXXXXXXXX
        export NO_PROXY=127.0.0.1,localhost,XXXXXXXXXXXX

        ```
    * Append below script in your host `~/.docker/config.json`.
      ```json
      {
        "proxies": {
          "default": {
            "httpProxy": "XXXXXXXXXXXX",
            "httpsProxy": "XXXXXXXXXXXX",
            "noProxy": "127.0.0.1,localhost,XXXXXXXXXXXX"
          }
        }
      }
      ```
    * Append below script in your host `/etc/docker/daemon.json`
      ```json
      {
        "proxies": {
          "http-proxy": "XXXXXXXXXXXX",
          "https-proxy": "XXXXXXXXXXXX",
          "no-proxy": "127.0.0.1,localhost,XXXXXXXXXXXX"
        }
      }
      ```
    * Append below scipt in your host `/etc/systemd/system/docker.service/docker.service.d/http-proxy.conf`
        > **OPTIONAL** Some older docker version might require this step.
        ```conf
        wuzhuobin@VM2:~/jscode/ChinaNgWaveViewWasm$ cat /etc/systemd/system/docker.service.d/http-proxy.conf
        [Service]
        Environment="HTTP_PROXY=XXXXXXXXXXXX"
        Environment="HTTPS_PROXY=XXXXXXXXXXXX"
        Environment="NO_PROXY=127.0.0.1,localhost,XXXXXXXXXXXX"
        ```
    * Run below scripts to configure docker proxy
        ```bash
        sudo systemctl daemon-reload
        sudo systemctl restart docker.service
        ```


## Usage
1. Press 'F1', then select 'Devcontainer: Reopen in container'. Then just wait
    the configuration finishes.
2. Install your own vscode extension.
3. Using the Makefile target to build.
    * `make all` Build the project.
    * `make clean` Remove all artifacts.
    * `make unit` Build unit tests.
    * `make coverage` Build unit tests and output coverage reports.
    * `make server` Hold the artifact in a test server. With forwarded ports
      provided by vscode, the output can be reviewed on your host's browser.
4. Have fun.
