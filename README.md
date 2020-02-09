Compile and run:
```
$ gcc invoke-function.c -o invoke-func
$ gcc simple.c -c -o simple
$ objcopy -O binary --only-section=.text ./simple ./simple.text
$ sudo ./invoke-func ./simple.text
result: 43
```
