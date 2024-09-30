# `c/mutable_environment`

This provides an example of a simple way to create a _mutable_ environment similar to `extern char **environ` in the standard library. I am using a fixed size buffer of pointers for the environment variables (i.e., there is a max number of environment variables supported).

## Build/Run


To build...
```bash
make test
```

To run the test...
```bash
./test
```
