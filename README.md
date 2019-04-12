# HVCommon

## Conan
   
### Build and test

```bash
conan create -tf tests/conan . hiventive/testing
```

### Push

```bash
conan upload hvcommon/VERSION@hiventive/testing --all -r=hiventive
```

## Logging levels

|   Level  |                 Description                                                                                                                                   |
|----------|---------------------------------------------------------------------------------------------------------------------------------------------------------------|                                                           |
| Trace    | Information that can be useful to back-trace certain events - mostly useful than debug logs.                                                                  |
| Debug    | Informational events most useful for developers to debug application. Only applicable if NDEBUG is not defined (for non-VC++) or _DEBUG is defined (for VC++).|
| Info     | Mainly useful to represent current progress of application.                                                                              |
| Warning  | Information representing errors in application but application will keep running. 
| Error    | Error information but will continue application to keep running.                                                                                              |
| Critical | Very severe error event that will presumably lead the application to abort.|

