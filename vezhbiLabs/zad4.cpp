#include <iostream>
#include <cstring>
using namespace std;
class County{
private:
    char name[30];
    int gdp;
public:
    County(){

    }
    County(char *name, int gdp){
        strcpy(this->name,name);
        this->gdp=gdp;
    }

    const char *getName() const {
        return name;
    }

    int getGdp() const {
        return gdp;
    }
};
class State{
private:
    County counties[100];
    char name[31];
    int numCounties;
    static float federalTax;
    bool redState;
public:
    State(){

    }
    State( County *counties, char *name, int numCounties, bool redState){
        for (int i = 0; i < numCounties; ++i) {
            this->counties[i]=counties[i];
        }
        strcpy(this->name,name);
        this->numCounties=numCounties;
        this->redState=redState;
//        federalTax++;
    }
    
    static float getFederalTax() {
        return federalTax;
    }

    static void setFederalTax(float fedTax) {
        State::federalTax = fedTax;
    }
    static float increaseFederalTax(float increase){
        State::federalTax+=increase;
    }
    float getFullGDP(){
        float vkupno=0;
        for (int i = 0; i < numCounties; ++i) {
            vkupno+=counties[i].getGdp();
        }
        vkupno = vkupno * (1.0 - federalTax/100);
        return vkupno;
    }
    void print(){
        cout<<"State of "<<name<<endl;
        for (int i = 0; i < numCounties; ++i) {
            cout<<counties[i].getName()<<endl;
        }
    }
    friend void printStatesInGDPOrderByStateType(State states[], int numStates, bool redStates);
};
void printStatesInGDPOrderByStateType(State states[], int numStates, bool redStates){

    for (int i = 0; i < numStates; ++i) {
        for (int j = 0; j < numStates-1; ++j) {
            if (states[i].getFullGDP() > states[j].getFullGDP()){
                State tmp = states[j];
                states[j]=states[j+1];
                states[j+1]=tmp;

            }
        }

    }
    if (redStates){
        for (int i = 0; i < numStates; ++i) {
            if (states[i].redState){
                cout<<states[i].name<<endl;
            }
        }
    }else {
        for (int i = 0; i < numStates; ++i) {
            if (!states[i].redState) {
                cout << states[i].name << endl;
            }
        }
    }
}
//main should remain unchanged!
float State::federalTax = 15.5;

int main() {
    int n;
    cin >> n;
    char name[30] = "Richmond";
    County counties[3];
    counties[0] = County(name, 20);
    strcpy(name, "Bronx");
    counties[1] = County(name, 57);
    strcpy(name, "New York");
    counties[2] = County(name, 32);
    State state(counties, name, 3, false);
    switch(n){
        case 1: {
            cout << "---Testing constructors, getters, setters---" << endl;
            float fed;
            cin >> fed;
            State::setFederalTax(fed);
            if (State::getFederalTax() == 15.5) {
                cout << "State federal tax setter not OK!";
                break;
            }
            cout << counties[2].getName() << " Federal tax: " << State::getFederalTax() << " Full GDP: "
                 << state.getFullGDP();
            break;
        }
        case 2: {
            cout << "---Testing print method---" << endl;
            char name2[50];
            cin >> name2;
            County counties2[4];
            for (int i = 0; i < 3; ++i) {
                counties2[i] = counties[i];
            }
            counties2[3] = County(name2, 27);
            State state2(counties2, name, 4, false);
            state2.print();
            break;
        }
        case 3: {
            cout << "---Testing increaseFederalTax static method---" << endl;
            float increase;
            cin >> increase;
            cout << State::getFederalTax() << endl;
            State::increaseFederalTax(increase);
            cout << State::getFederalTax() << endl;
            cout << state.getFullGDP();
            break;
        }
        default:
            cout << "---Testing printStatesInGDPOrderByStateType---" << endl;
            County counties2[4];
            for (int i = 0; i < 3; ++i) {
                counties2[i] = counties[i];
            }
            strcpy(name, "Wayme");
            counties2[3] = County(name, 27);
            strcpy(name, "Ohio");
            State state2(counties2, name, 4, false);
            int numStates;
            cin >> numStates;
            numStates = numStates + 2;
            State states[numStates];
            states[0] = state;
            states[1] = state2;
            bool redStateSType;
            for (int i = 2; i < numStates; ++i) {
                char stateName[30];
                int numCounties;
                cin >> stateName >> numCounties >> redStateSType;
                County county[numCounties];
                for (int j = 0; j < numCounties; ++j) {
                    char ime[30];
                    int GDP;
                    cin >> ime >> GDP;
                    county[j] = County(ime, GDP);
                }
                states[i] = State(county, stateName, numCounties, redStateSType);
            }
            cout << "Red states: "<<endl;
            printStatesInGDPOrderByStateType(states, numStates, true);
            cout << "Blue states: "<<endl;
            printStatesInGDPOrderByStateType(states, numStates, false);

    }
    return 0;
}
