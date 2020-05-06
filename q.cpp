#include<iostream>
void f(std::string s = "huy", int x = 5) {
    std::cout << s << " |  " << x << '\n';
}

int main(){
    f("jopa");
    f(3);
}
