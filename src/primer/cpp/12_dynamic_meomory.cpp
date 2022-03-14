/*
 * 12.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: wangwei69
 */

#include "all.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

/*
 * chapter 12 : ����ָ��
 *
 *
 * Ŀ�ģ� ʹ������ָ�룬�����Զ������ڴ���ͷţ���Ҫ����heep���ģ�
 * ͷ�ļ���<memory>
 *
 * ���� shared_ptr
 *

 *
 * ��ָ�룺 weak_ptr

 *
 *
 * ��ռ��unique_ptr
 *

 *
 *
 *
 *
 *
 *˼����
 * 1��Ϊʲô��Ҫ��̬�����ڵ���Դ���ࣿ
 *
 *   ��֪����Ҫ�ö��ٸ�����
 *   �������乲�����ݣ�
 *      �Զ���ĳ���࣬���ඨ��Ķ������֮�䣬���Թ������ݳ�Ա�е����ݣ�
 *   ��֪�������׼ȷ���ͣ�
 *
 * 2���ڴ�й¶������ָ�룿
 *
 *   memeory leak :  δ�ͷŶ�̬������ڴ档һ���������:delete ��
 *   dangling pointer:  delete ptrָ���ڴ������ptr��ʵ�������ַ���ݣ���ʱΪ���������������delete֮��ֵnullptr��
 *
 *
 */



/*
 * ϣ�������Ķ������ͨ��shared_ptr���Թ���ײ�data���ݣ���ʲô�����»��ã�
 *
 * ���ۣ� ��������ָ���࣬��ô���ʵ�֣�
 *
 */


class strBlob{

friend class strBlobPtr;

public:

    using size_type = vector<string>::size_type;
    strBlob();
    strBlob(initializer_list<string> li);

    size_type get_size(){
        return data->size();
    }

    long get_point_cnt(){
        return data.use_count();
    }


private:
    shared_ptr<vector<string>> data;

};

strBlob::strBlob():data(make_shared<vector<string>>()){}
strBlob::strBlob(initializer_list<string> li):data(make_shared<vector<string>>(li)){}


/*
 * ����ָ����
 * Ŀ��: ?   ����ָ�������ͱ��������ʹ����ͬ�ĵײ����ݡ�
 *          ����ָ�������ʹ��cur���������Ԫ��
 *
 */


class strBlobPtr{

public:

    strBlobPtr():cur(0){};
    strBlobPtr(strBlob &a, size_t idx = 0): wptr(a.data),cur(idx){}; //�����õ�strBlob������˽������a������ʼ����Ա��������ô�죿 friend

    string& deref() const;  //ͨ���������ָ�룬������ԭ���������ݣ�
    strBlobPtr& incr();  //�������ָ��


private:
    weak_ptr<vector<string>> wptr;
    size_t cur;
    shared_ptr<vector<string>> check(size_t idx, const string &str)const;

};


//���Ϸ���
shared_ptr<vector<string>> strBlobPtr::check(size_t idx, const string& msg) const{

    shared_ptr<vector<string>> it = wptr.lock();  //ͨ��weak_ptr������shared_ptr....

    if (!it){ //shared_ptr���ü����Ѿ�Ϊ0��
        throw std::runtime_error("unbound shared ptr!"); //�׳�����ʱ�쳣
    }
    if (idx >= it->size()){ //�±곬����
        throw std::out_of_range(msg);  //�׳�Խ���쳣
    }
    return it;
}

//�����ò���
string& strBlobPtr::deref() const{
    auto sptr = check(cur, "dereference failed!");
    return (*sptr)[cur]; //
}

strBlobPtr& strBlobPtr::incr(){

    check(cur, "out of range");
    ++cur; //����cur�����һ����++cur�ͳ����˰���
    return *this;

}



void test_12(){

    /*
     * shared_ptr
     *  ģ���ࣺ shared_ptr<OBJ_TYPE> p;
     *          p : p�Ƿ�ָ��һ�������ǵĻ�������true�����򷵻�false��
     *
     *          *p :
     *          p->mem:
     *
     *          p.get() : ����p�����ָ�룻
     *
     *          swap(p,q) : ��������ָ����н���
     *
     *  ���еĲ�����
     *
     *        make_shared<OBJ_TYPE>(args) :
     *        ʹ��args����OBJ_TYPE���Ͷ���(���������Ҫ�����๹�캯����Ҫ��)��������ָ��ö����shared_ptrָ�룻
     *
     *        ��̬�����ڴ沢��ʼ�����쳣��ȫ��
     *
     *        shared_ptr<OBJ_TYPE> p(q) : q ���� p��ָ��ͬһ������qָ�����������1��
     *
     *        p = q �� p�ļ������ݼ���q�����ü��������������pָ���ԭ���Ĳ��֣����������0�ˣ���Ҫ�ͷ��ڴ棻
     *
     *        p.unique(): �ж�pָ��Ķ������ü����Ƿ�Ϊ1��
     *
     *        p.use_count():
     *
     */

    strBlob str1;

    //�޶�str2�ɼ���Χ
    {
        strBlob str2({"wang","wei","ni","hao"});
        str1 = str2;
        //��������str2�����ͷţ���str2�д��������ݻ����еģ���Ϊ==�������data�� str2 ���ü�����++��str1��data�ͷ�ԭ��ָ�����ݣ�ָ��str2��data��
    }

    //str2�������Ƿ񻹴��ڣ�str1��data�����ü������ĸ�����

    cout << "str1 can remain str2 data ? size:  " << str1.get_size() << " pointer cnt: "  << str1.get_point_cnt()<< endl;

    strBlob &str3 = str1;
    cout << " pointer cnt: "  << str3.get_point_cnt()<< endl; //shared_ptr ��������ã����������ü�������ֵ��

    strBlob str4 = str1;
    cout << " pointer cnt: " << str4.get_point_cnt() << endl;


    strBlobPtr str1_ptr(str1, 1);

    cout << "strBlobPtr deref: " << str1_ptr.deref() << endl;
    str1_ptr.incr();
    cout << "strBlobPtr after incr deref : " << str1_ptr.deref() << endl;

    /*
     * weak_ptr
     *       ʹ�ó����� ָ����shared_ptr����Ķ��󣻲�����shared_ptr�����ü�������ֵ����ʹ��weak_ptrָ��shared_ptrҲ���ܱ�����
     *
     *       w.expired() : shared_ptr������Ϊ0�ˣ��ͳ����ˣ�����true;���򷵻�false;
     *
     *       w.lock() :  ûexpired������£�����ָ��wd�Ķ����shared_ptr;���򷵻أ��յ�shared_ptr��
     *
     *       w = p :  p��shared_ptr��weak_ptr,���������ü�����ֵ��w,pָ����ͬ�Ķ���
     *
     */

    shared_ptr<vector<string>> s_str_ptr(new vector<string>(10, "wang"));

    cout << "shared_ptr : " << (*s_str_ptr)[1] << " shared count: "<< s_str_ptr.use_count()<<endl;

    weak_ptr<vector<string>> w_str_ptr;
    w_str_ptr = s_str_ptr;

    //cout << "weak_ptr : " << (*w_str_ptr)[1] << endl;
    cout << "weak_ptr : " << (*w_str_ptr.lock())[1] << endl;  //weak_ptr����ֱ�����ã���Ҫͨ��lock��ȡshared_ptr�����ã�



    /*
     * unique_ptr
     *
     *  ���ܸ�ֵ�Ϳ��������Է���ת�ƣ�
     *      unique_ptr<OBJ_TYPE> ptr (new OBJ_TYPE(args)) : ��ռָ��һ����new����ֱ�ӳ�ʼ����
     *      p.release() : �ͷ�p����Ȩ��p�ÿգ������ض�Ӧָ�룻 ��ԭ�����ڴ滹�ڡ�
     *      p.reset(): �ͷ�pָ������ڴ�Ҳ�ͷ��ˡ�
     *      p.reset(q.realease()) :  ת�ƿ���Ȩ��q�ÿգ��ͷſ���Ȩ������ԭ���ڴ�ָ����ָ��p�ϣ���������Ȩ��ת�ƣ�
     *      ��Ƶ���ģʽʱ: ����ʹ�ö�ռָ�룬ָ��ͳһ�����ݴ�����
     *
     */

    /*
    ��ʼ����ʽ
����1. ֱ�ӳ�ʼ����unique<T> myPtr(new T);  //ok��������ͨ����ʽת�������죬��unique<T> myPtr = new T()����Ϊunique_ptr���캯��������Ϊexplicit��
����2. �ƶ����죺unique<T> myOtherPtr = std::move(myPtr);���������ƹ��죬��unique<T> myOther = myPtr; ��Ϊunique�Ǹ�ֻ�ƶ����͡�
����3. ͨ��make_unique���죺unique<T> myPtr = std::make_unique<T>(); //C++14֧�ֵ��﷨������make_����֧�����ɾ���������߳�ʼ���б�
����4. ͨ��reset���ã���std::unique_ptr up; up.reset(new T());
   */

    unique_ptr<vector<string>> str_ptr(new vector<string>(10, "test"));

    unique_ptr<vector<string>> str_ptr_other;
    str_ptr_other.reset(str_ptr.release());  //unique_ptr ��������Ȩ��ת��

    cout << "unique_ptr use: " << (*str_ptr_other)[2] << endl;



    /*
     * topic  ��̬����
     *
     *
     *
     *
     */


    size_t len = 10;
    int *ptr = new int[len]; //δ��ʼ��
    int *ptr2 = new int[10](); //Ԫ��ֵ����ʼ��Ϊ0

    int *ptr3 = new int[len]{1,2,3,4,5}; //����ֱ����{}����ʼֵ

    //int *ptr4 = new int[3]{1,2,3,4}; //Ԫ�ظ�������������ռ��С���׳��쳣��bad_array_new_length ͷ�ļ�<new>

    delete []ptr; //new�����Ҫdelete������Ҫ��[];
    delete []ptr2;
    delete []ptr3;



    /*
     * topic  allocator  <memory>
     *
     *    �ڴ�ķ��� �� ���� �ֿ��� new ������һ�𣬿�����ɲ���Ҫ�ļ����˷ѣ��ำֵһ�Σ�
     *
     *    allocator<T> a  : ����һ���������Ķ���
     *
     *    p = a.allocate(n) : ����n��δ�õ��ڴ�ռ�; ���� T* p��
     *
     *    a.deallocate(n) : ����n��������ڴ�ռ䣻ע�⣬�ڻ����ڴ�֮ǰ����Ҫdestroy�ڴ��ж���Ҳ��������������
     *
     *    a.construct(p, args) : ��ָ��p��ָλ���ϣ���������T�Ķ���argsƥ����Ӧ�Ĺ��캯��
     *
     *    a.destory(p) :  ָ��p��ָ���󣬽�������������
     *
     *
     *
     *
     */


    allocator<string> alloc;
    string *str_ptr_al = alloc.allocate(10); //����10��װstring�����ԭ���ڴ�ռ䣻

    auto p = str_ptr_al;
    alloc.construct(p, "wang");
    alloc.construct(++p, "wei");

    cout << "allocator str: " << str_ptr_al[0] << endl;
    cout << "allocator str: " << str_ptr_al[1] << endl;





}



