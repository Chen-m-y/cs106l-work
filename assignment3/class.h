#include <string>
#include <utility>
template <typename T>
struct Vec2{
    T x = T{};
    T y = T{};

    Vec2() = default;
    Vec2(T x_, T y_): x(x_),y(y_){};
};

template <typename T>
class BasicObject{
private:
    Vec2<T> pos;
    Vec2<T> vel; 
    std::string name;
    void sanitizeName();
    void integrate(T dt) noexcept; // 积分
public:
    BasicObject();
    BasicObject(Vec2<T> pos, Vec2<T> vel, std::string name);
    Vec2<T> getPos() const;
    Vec2<T> getVel() const;
    const std::string& getName() const; 
    void setPos(T x, T y);//函数内修改只能修改副本/原来的根本不变/const没用
    void setVel(T vx, T vy);
    void setName(const std::string& s);
    //保护调用方的原始字符串不被你篡改,必须加，否则调用方不敢传临时值/字面量
    void update(T dt);
};

#include "class.cpp"

