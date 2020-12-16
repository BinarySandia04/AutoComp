// (c) Aran Roig, 2019 - 2020
// Agradecimientos a izanbf por inspirarme un poco con su propio debug.h

template <class T>
void debug(T t){ std::cout << t << "\n";}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& obj)
{   
    os << "{";
    int limit = obj.size();
    for(int i = 0; i < limit; i++){
        if(i != limit - 1) os << obj[i] << ", ";
        else os << obj[i] << "}";
    }
    return os;
}

template <typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& obj){
    os << "(" << obj.first << ", " << obj.second << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const bool& obj)
{
    if(obj) os << "\'True\'";
    else os << "\'False\'";
    return os;
}
