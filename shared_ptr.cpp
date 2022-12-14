#include <iostream>
using namespace std;
template <typename T>
class shared_ptr
{
private:
    T* m_ptr;
    int* m_count;
public:
    shared_ptr(T* p = NULL):m_ptr(p)
    {
        if (m_ptr)
        {
            m_count = new int(1);
        }
        else
        {
            m_count = new int(0);
        }

    }
    /* 拷贝构造函数，需要注意判断是否是自我赋值 */
    shared_ptr(const shared_ptr& p)
    {
        if (m_ptr != p.m_ptr)
        {
            m_ptr = p.m_ptr;
            m_count = p.m_count;
            (*m_count)++;
        }
    }

    ~shared_ptr()
    {
        printf("destroy %p\n", this);
        (*m_count)--;
        if (*m_count == 0)
        {
            delete m_ptr;
            delete m_count;
        }
    }

    /* 拷贝赋值三部曲：1、判断是否自我赋值； 2、删除拷贝的相应内容；3、进行复制操作 */
    shared_ptr& operator=(const shared_ptr& p)
    {
        if(m_ptr == p.m_ptr)
        {
            return *this;
        }

        if (m_ptr)
        {
            (*m_count)--;
            if (*m_count == 0)
            {
                printf("current count is 0, destroy heap\n");
                delete m_ptr;
                delete m_count;
            }
        }

        m_ptr = p.m_ptr;
        m_count = p.m_count;
        (*m_count)++;

        return *this;
    }

    T* operator->()
    {
        assert(m_ptr);
        return m_ptr;
    }
    T& operator*()
    {
        assert(m_ptr);
        return *m_ptr;
    }

    int use_count()
    {
        return *m_count;
    }

};
int main()
{
    shared_ptr<int> p1;
    shared_ptr<int> p2(new int(5));
    cout<<"p1 m_count = "<<p1.use_count()<<endl; // 0
    cout<<"p2 m_count = "<<p2.use_count()<<endl; // 1
    cout<<endl;

    p1 = p2;
    cout<<"p1 m_count = "<<p1.use_count()<<endl;   // 2
    cout<<"p2 m_count = "<<p2.use_count()<<endl;    // 2
    cout<<endl;

    shared_ptr<int> p3(p1);
    cout<<"p1 m_count = "<<p1.use_count()<<endl;   // 3
    cout<<"p2 m_count = "<<p2.use_count()<<endl;    // 3
    cout<<"p3 m_count = "<<p3.use_count()<<endl;    // 3
    return 0;
}
