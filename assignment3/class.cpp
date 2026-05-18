
// default constructor
template <typename T>
BasicObject<T>::BasicObject() = default;
 // parameterized constructor
template <typename T>
BasicObject<T>::BasicObject(Vec2<T> pos, Vec2<T> vel, std::string name){
    this->pos = pos;
    this->vel = vel;
    this->name = name;
    sanitizeName();
}
//------------GETTER-------------
template <typename T>
Vec2<T> BasicObject<T>::getPos() const{
    return pos;
}
template <typename T>
Vec2<T> BasicObject<T>::getVel() const{
    return vel;
}
template <typename T>
const std::string& BasicObject<T>::getName() const{
    return name; // 还是写 return name; 不需要加 &
}
//------------SETTER-------------
template <typename T>
void BasicObject<T>::setPos(T x, T y){
    pos.x = x;
    pos.y = y;
}
template <typename T>
void BasicObject<T>::setVel(T vx, T vy){
    vel.x = vx;
    vel.y = vy;
}
template <typename T>
void BasicObject<T>::setName(const std::string& s){
    if(!s.empty()){
        name = s;
    }
}

template <typename T>
void BasicObject<T>::sanitizeName(){
    if(name.empty()){
        name = "UnnamedObject";
    }
}
template <typename T>
void BasicObject<T>::integrate(T dt) noexcept{
    pos.x += vel.x *dt;
    pos.y += vel.y *dt;
}
template <typename T>
void BasicObject<T>::update(T dt){
    integrate(dt);
}
