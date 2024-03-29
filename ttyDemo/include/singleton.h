#pragma once

template<typename T>
class Singleton
{
public:
    static T& GetInstace()
    {
        static T instance;
        return instance;
    }
protected:
    Singleton(){}
    ~Singleton(){}
private:
    Singleton(const Singleton& other);
    Singleton& operator=(const Singleton& other);
};
