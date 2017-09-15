#include<stdio.h>
#include<jni.h>
#include <sys/time.h>	// struct timeval 和gettimeofday函数的头文件
#include <string.h>     // 处理字符串相关, http://www.cnblogs.com/52php/p/5724382.html

// jstring Java_com_example_data_MainActivity_getIp(JNIEnv* env,jobject jobj)
//   {
//       return (*env)->NewStringUTF(env,"192.168.31.225");
//   }


/*
    Java类型签名:
    Java 类型	类型签名
    boolean	Z
    byte	B
    char	C
    short	S
    int	I
    long	L
    float	F
    double	D
    类	L全限定名;，比如String, 其签名为Ljava/lang/util/String;
    数组	[类型签名， 比如 [B

    学习博客: http://blog.csdn.net/qinjuning/article/details/7607214
*/

/*
    jni 接口编写规范:
    jstring, 返回值为Java中的string类型
    调用方法的对象为: com.example.jni.Test, sayHello函数
    JNIEnv* env表示的是虚拟机指针
    jCallerObj, 表示的是调用native方法的Java对象
*/
jstring Java_com_example_jni_Test_sayHello(JNIEnv* env,jobject javaNativeCaller)
{
    return (*env)->NewStringUTF(env,"hello world");
}

jobjectArray Java_com_example_jni_Test_getLink(JNIEnv* env,jobject obj)
{
    // 返回一个string数组
    // 先创建两个字符串
    char* ip = "192.168.31.225";
    char* port = "9800";

    // 查找Java中的String类
    jclass jstrClass = (*env)->FindClass(env,"java/lang/String");
    // 最后一个参数是初始化值得意思, 传入NULL 即可
    // 接口名: NewObjectArray(JNIEnv* env,jsize,jclass,jobject);
    jobjectArray jStrArr = (*env)->NewObjectArray(env,2,jstrClass,NULL);

    // 创建Java字符串: ip地址
    jstring ipStr = (*env)->NewStringUTF(env,ip);
    // 创建Java字符串, 端口号
    jstring portStr = (*env)->NewStringUTF(env,port);
    // 设置数组中的元素
    (*env)->SetObjectArrayElement(env,jStrArr,0,ipStr);
    (*env)->SetObjectArrayElement(env,jStrArr,1,portStr);
    // JNI DETECTED ERROR IN APPLICATION: cannot assign object of type 'com.example.data.MainActivity' to array with element type of 'java.lang.String'
    // jstring 其实和jobject是一样的, typedef jobject jstring
    return jStrArr;
}

// 返回一个赋过值得NetInfo对象
jobject Java_com_example_jni_Test_getNetInfo(JNIEnv* env,jobject obj)
{

    // 找到字节码对象
    // jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jNetInfoClazz = (*env)->FindClass(env,"com/example/jni/NetInfo");

    // 分配一个对象, alloc
    // jobject     (*AllocObject)(JNIEnv*, jclass);
    jobject jNetInfoObject = (*env)->AllocObject(env,jNetInfoClazz);

    // 找到对象中的字段id
    // 参数一, 类的jclass; 参数二, 字段名; 参数三,字段的类型签名
    //  jfieldID GetFieldID(jclass clazz, const char* name, const char* sig)
    // 参数一是虚拟机指针, 参数二是NetInfo的jclass值,第三个参数是类的字段名,第四个参数是字段的类型的签名
    // java对象的签名: Ljava/com/lang/String;  必须是分号隔开或结束
    // L是Java数据类型Object的签名类型L, java/lang/String是
    jfieldID jNetInfo_IP = (*env)->GetFieldID(env,jNetInfoClazz,"ip","Ljava/lang/String;");
    jfieldID jNetInfo_port = (*env)->GetFieldID(env,jNetInfoClazz,"port","I");

    //  void        (*SetObjectField)(JNIEnv*, jobject, jfieldID, jobject);
    jstring ipStr = (*env)->NewStringUTF(env,"192.168.31.228");
    (*env)->SetObjectField(env,jNetInfoObject,jNetInfo_IP,ipStr);

    //     void        (*SetIntField)(JNIEnv*, jobject, jfieldID, jint);
    (*env)->SetIntField(env,jNetInfoObject,jNetInfo_port,9800);

    return jNetInfoObject;
}

jboolean Java_com_example_jni_Test_getBoolean(JNIEnv* env,jobject jNativeCaller,jboolean jboo)
{
    // JNI_TRUE, 在jni.h中定义了, 是1; 到Java层后是true
    // JNI_FALSE, 在jni.h中定义了, 是0, 到Java层是false

    /*
    if(i % 2 == 0) return JNI_TRUE;
    else return JNI_FALSE;
    */
    if(jboo == JNI_TRUE) return JNI_FALSE;
    else return JNI_TRUE;
}

jint Java_com_example_jni_Test_getInt(JNIEnv* env,jobject jNativeCaller,jint i)
{
    return i * 100;
}

jbyte Java_com_example_jni_Test_getByte(JNIEnv* env,jobject jNatuveCaller,jint jb)
{
    if(jb > 255)
    {
        jb = jb % 256;
    }
    return jb;
}

jchar Java_com_example_jni_Test_getChar(JNIEnv* env,jobject jobj,jchar jc)
{
    return jc;
}

jshort Java_com_example_jni_Test_getShort(JNIEnv* env,jobject jobj)
{
    return 268;
}

jlong Java_com_example_jni_Test_getLong(JNIEnv* env,jobject jobj)
{
    // 申明一个结构体对象
    struct timeval t;
    // 获取时间, 时间会赋值给t
    gettimeofday(&t,NULL);
    // 返回值是微秒
    // t.tv_sec是秒的部分
    // t.tv_usec是微秒部分; 要组成毫秒值, 则需要秒*1000, 微秒/1000, 相加
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}

jfloat Java_com_example_jni_Test_getFloat(JNIEnv* env,jobject obj)
{
    // c语言中的float位数和Java的一致, 4位
    float pa = 3.14;
    return pa;
}

jdouble Java_com_example_jni_Test_getDouble(JNIEnv* env,jobject obj)
{
    double p = 3.141592654;
    return p;
}

jintArray Java_com_example_jni_Test_getInts(JNIEnv* env,jobject obj,jint size)
{
    jintArray jiArr = (*env)->NewIntArray(env,size);
    return jiArr;
}

jbooleanArray Java_com_example_jni_Test_getBooleans(JNIEnv* env,jobject obj,jint size)
{
    jbooleanArray jbArr = (*env)->NewBooleanArray(env,size);
    /*
    int len = size;
    jboolean *h = new jboolean[len];
    for(int i = 0;i < len;i ++)
    {
        h[i] = i % 2;
    }
    // 类似于Java的System.arrayCopy();
    // 参数一是目标数组对象, 参数二是其实位置, 参数三是长度, 参数四的源数组
    (*env)->SetBooleanArrayRegion(jbArr,0,size,h);
    */
    jboolean *jb = (*env)->GetBooleanArrayElements(env,jbArr,NULL);
    for(int i = 0;i < size;i ++)
    {
        jb[i] = i % 2;
    }
    (*env)->ReleaseBooleanArrayElements(env,jbArr,jb,0);
    return jbArr;

    //return jbArr;
}

jbyteArray Java_com_example_jni_Test_getBytes(JNIEnv* env,jobject obj,jint size)
{
    jbyteArray jbyArr = (*env)->NewByteArray(env,size);
    return jbyArr;
}

jcharArray Java_com_example_jni_Test_getChars(JNIEnv* env,jobject obj,jint size)
{
    jcharArray jcArr = (*env)->NewCharArray(env,size);
    return jcArr;
}

jshortArray Java_com_example_jni_Test_getShorts(JNIEnv* env,jobject obj,jint size)
{
    return (*env)->NewShortArray(env,size);
}

jlongArray Java_com_example_jni_Test_getLongs(JNIEnv* env,jobject obj,jint size)
{
    return (*env)->NewLongArray(env,size);
}

jfloatArray Java_com_example_jni_Test_getFloats(JNIEnv* env,jobject obj,jint size)
{
    return (*env)->NewFloatArray(env,size);
}

jdoubleArray Java_com_example_jni_Test_getDoubles(JNIEnv* env,jobject obj,jint size)
{
    return (*env)->NewDoubleArray(env,size);
}

jobjectArray Java_com_example_jni_Test_getIntArrays(JNIEnv* env,jobject obj,jint size)
{
    /*
    // PS: 注意: (*env)->FindClass(env,"[I");是linux下c语言的调用方式
    // env->FindClass("[I");是c++的调用方式; 如果要使用c++的调用方式, 把文件改为.cpp即可
    jclass intArrClass = env->FindClass("[I");
    //jobjectArray NewObjectArray(jsize length, jclass elementClass,jobject initialElement)
    // 创建一个int的二维数组
    jobjectArray intObjectArr = env->NewObjectArray(size,intArrClass,NULL);

    for(int i = 0;i < size;i++)
    {
        jintArray intArray = env->NewIntArray(size);

        jint temp[size];
        for(int j = 0;j < size;j++)
        {
            temp[j] = i * 10 + j;
        }
        // SetIntArrayRegion(jintArray array, jsize start, jsize len,const jint* buf)
        env->SetIntArrayRegion(intArray,0,size,temp);

        env->SetObjectArrayElement(intObjectArr,i,intArray);

        env->DeleteLocalRef(intArray);
    }
    return intObjectArr;
    */

    jclass intArrClass = (*env)->FindClass(env,"[I");
        //jobjectArray NewObjectArray(jsize length, jclass elementClass,jobject initialElement)
        // 创建一个int的二维数组
        jobjectArray intObjectArr = (*env)->NewObjectArray(env,size,intArrClass,NULL);

        for(int i = 0;i < size;i++)
        {
            jintArray intArray = (*env)->NewIntArray(env,size);

            jint temp[size];
            for(int j = 0;j < size;j++)
            {
                temp[j] = i * 10 + j;
            }
            // SetIntArrayRegion(jintArray array, jsize start, jsize len,const jint* buf)
            (*env)->SetIntArrayRegion(env,intArray,0,size,temp);

            (*env)->SetObjectArrayElement(env,intObjectArr,i,intArray);

            (*env)->DeleteLocalRef(env,intArray);
        }
        return intObjectArr;
}

// native调用Java层函数
// can't call void com.example.jni.Test.callByNative(java.lang.String) on instance of java.lang.Class<com.example.jni.Test>
// 必须静态方法回调到静态方法, 非静态回调到非静态, 上面这个报错是因为程序里的静态方法回调到了非静态方法
void Java_com_example_jni_Test_callNative(JNIEnv* env,jobject obj)
{
    // void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...)
    jstring jstr = (*env)->NewStringUTF(env,"string from native");

    // jclass      (*GetObjectClass)(JNIEnv*, jobject);
    // jclass mjclazz = (*env)->GetObjectClass(obj);    // 这里的obj其实指向的是调用者,
                                                        // 刚好调用者也是native要调用的方法所在的类
    // jclass      (*FindClass)(JNIEnv*, const char*);
    jclass mjclazz = (*env)->FindClass(env,"com/example/jni/Test");
    // jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    jmethodID callByNativeId = (*env)->GetMethodID(env,mjclazz,"callByNative","(Ljava/lang/String;)V");

    // 这里要使用obj, 因此Java层对应的native不能为静态方法
    // ...是参数
    (*env)->CallVoidMethod(env,obj,callByNativeId,jstr);
}

// isNull为静态方法的时候, 测试obj是否为NULL
jboolean Java_com_example_jni_Test_isNull(JNIEnv* env,jobject obj)
{
    // false
    if(obj == NULL) return JNI_TRUE;
    else return JNI_FALSE;
}

// 返回一个Person对象
jobject Java_com_example_jni_Test_birth(JNIEnv* env,jobject obj)
{


    // jclass      (*FindClass)(JNIEnv*, const char*);
    jclass jPersonClazz = (*env)->FindClass(env,"com/example/bean/Person");

    // 第四个参数是descriptor, 方法签名;, 可以在字节码的包名目录下, 执行javap -s com.example.bean.Person
    // 构造方法的方法名默认为"<init>"
    // methodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    jmethodID jPersonConstructMethodID = (*env)->GetMethodID(env,jPersonClazz,"<init>","(Ljava/lang/String;I)V");

    jstring name = (*env)->NewStringUTF(env,"袁光芯");
    jint age = 25;
    // 创建对象
    // jobject     (*NewObject)(JNIEnv*, jclass, jmethodID, ...);
    return (*env)->NewObject(env,jPersonClazz,jPersonConstructMethodID,name,age);
}

void Java_com_example_jni_Test_callbackByNative(JNIEnv* env,jobject obj,jobject p)
{

    // ------------------------------------------------------------------------- //
    jclass jpersonClazz = (*env)->GetObjectClass(env,p);
    // 第一步, 将对象解析拼接成字符串
    // jfieldID    (*GetFieldID)(JNIEnv*, jclass, const char*, const char*);
    jfieldID ageFieldID = (*env)->GetFieldID(env,jpersonClazz,"age","I");
    jfieldID nameFieldID = (*env)->GetFieldID(env,jpersonClazz,"name","Ljava/lang/String;");
    // jint       (*GetIntField)(JNIEnv*, jobject, jfieldID);
    jint age = (*env)->GetIntField(env,p,ageFieldID);
    jstring name = (*env)->GetObjectField(env,p,nameFieldID);

    // const jchar* (*GetStringChars)(JNIEnv*, jstring, jboolean*);
    // const char* buf = (*env)->GetStringUTFChars(env,name,NULL);

    // sprintf(s, "%s love %s.", who, whom); //产生："I love CSDN. "
    // sprintf(buf," %d",age);
    // jstring toString = (*env)->NewStringUTF(env,buf);
    // void        (*ReleaseStringUTFChars)(JNIEnv*, jstring, const char*);
    // (*env)->ReleaseStringUTFChars(env,toString,buf);
    // ------------------------------------------------------------------------- //


    // jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    jclass jtestClazz = (*env)->FindClass(env,"com/example/jni/Test");
    jmethodID callbackMethodID = (*env)->GetMethodID(env,jtestClazz,"callByNative","(Ljava/lang/String;)V");

    jstring str = (*env)->NewStringUTF(env,"hahaha, ");
    // void        (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
    (*env)->CallVoidMethod(env,obj,callbackMethodID,name);  // 这里的jnit age不能当成jobject传, 程序会崩溃的, 而且看不到是哪里错
}

// 函数必须定义在调用者的前面
jobject createPerson(JNIEnv* env,jstring name,jint age)
{
    jclass personClazz = (*env)->FindClass(env,"com/example/bean/Person");
    jmethodID jpersonCon = (*env)->GetMethodID(env,personClazz,"<init>","(Ljava/lang/String;I)V");
    // jobject     (*NewObject)(JNIEnv*, jclass, jmethodID, ...);
    return (*env)->NewObject(env,personClazz,jpersonCon,name,age);
}

jobject Java_com_example_jni_Test_getListStudent(JNIEnv* env,jobject obj)
{

    jclass jArrayListClazz = (*env)->FindClass(env,"java/util/ArrayList");
    // jmethodID   (*GetMethodID)(JNIEnv*, jclass, const char*, const char*);
    jmethodID jconstruct = (*env)->GetMethodID(env,jArrayListClazz,"<init>","()V");
    // jobject     (*NewObject)(JNIEnv*, jclass, jmethodID, ...);
    jobject jArrayListObj = (*env)->NewObject(env,jArrayListClazz,jconstruct);

    jmethodID jAdd = (*env)->GetMethodID(env,jArrayListClazz,"add","(Ljava/lang/Object;)Z");

    for(int i = 0;i < 3;i++)
    {
        jobject person = createPerson(env,(*env)->NewStringUTF(env,"袁光芯"),25+i);
        // jboolean    (*CallBooleanMethod)(JNIEnv*, jobject, jmethodID, ...);
        (*env)->CallBooleanMethod(env,jArrayListObj,jAdd,person);
    }

    return jArrayListObj;
}
