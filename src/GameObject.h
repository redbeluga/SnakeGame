#include <iostream>
#include <list>

class GameObject{
  public:
    std::pair<int, int> loc;
    GameObject* p;
    std::list<GameObject> c;

    std::pair<int, int> getLoc();
    void sayHi(){std::cout << "Locked and Loaded"; }
    GameObject getParent();
    
    GameObject(std::pair<int, int> loc, GameObject* parent);
    GameObject(std::pair<int, int> loc);
};