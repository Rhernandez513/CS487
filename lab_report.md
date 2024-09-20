## Environment Variable and Set-UID Program Lab

Robert D. Hernandez rherna70@uic.edu

REF: https://seedsecuritylabs.org/Labs_20.04/Files/Environment_Variable_and_SetUID/Environment_Variable_and_SetUID.pdf

This lab covers the following topics:

- Environment variables
- Set-UID programs
- Securely invoke external programs
- Capability leaking
- Dynamic loader/linker

### 2.1 Task 1: Manipulating Environment Variables

```sh
$ env | grep VSCODE

> VSCODE_GIT_ASKPASS_EXTRA_ARGS=
> VSCODE_GIT_ASKPASS_MAIN=/home/ubuntu/.vscode-server/cli/servers/Stable-38c31bc77e0dd6ae88a4e9cc93428cc27a56ba40/server/extensions/git/dist/askpass-main.js
> VSCODE_GIT_ASKPASS_NODE=/home/ubuntu/.vscode-server/cli/servers/Stable-38c31bc77e0dd6ae88a4e9cc93428cc27a56ba40/server/node
> VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-9ff3d47ffd.sock
> VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-2511cd67-320e-4152-91df-2c49b8851ad2.sock
```


```sh
$ export HELLO="WORLD"
$ echo $HELLO
> WORLD
```

```sh
$ unset HELLO
$ echo $HELLO
>
```

2.2 Task 2: Passing Environment Variables from Parent Process to Child Process