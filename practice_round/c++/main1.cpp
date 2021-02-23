#include<bits/stdc++.h>

using namespace std;

using ll=long long;

using lui=long unsigned int;

struct Pizza{
    ll id;
    vector<ll> ingredients;
};

class Group{
    public:
        lui size;
        vector<ll> pizzas;
        vector<ll> ingredients;
        Group(int size);
        void print();
        void add_pizza(Pizza &pizza);
        lui score();
};

Group::Group(int size){
    this->size = size;
}

void Group::add_pizza(Pizza &pizza){
    this->pizzas.push_back(pizza.id);
    vector<ll> s3;
    set_union(pizza.ingredients.begin(),pizza.ingredients.end(),this->ingredients.begin(),this->ingredients.end(), back_inserter(s3));
    this->ingredients = s3;
}

lui Group::score(){
    if(pizzas.size()!=size) return 0;
    return ingredients.size()*ingredients.size();
}

void Group::print(){
    cout << pizzas.size() << " ";
    for(lui i=0; i<pizzas.size(); ++i){
        if(i==pizzas.size()-1){
            cout << pizzas[i] << "\n";
            return;
        }
        cout << pizzas[i] << " ";
    }
}

ll inter(vector<ll> &s1, vector<ll> &s2){
    vector<ll> s3;
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(), back_inserter(s3));
    return s3.size();
}


int main(){
    ll M, T2, T3, T4;
    cin >> M >> T2 >> T3 >> T4;
    
    unordered_map<string, ll> ingredients;
    vector<Pizza> pizzas;
    for(ll i=0; i<M ;++i){
        Pizza p;
        p.id = i;
        ll I;
        cin >> I;
        for(ll j=0; j<I ;++j){
            string ingredient;
            cin >> ingredient;
            if(ingredients.count(ingredient)==0){
                ingredients[ingredient] = ingredients.size();
            }
            p.ingredients.push_back(ingredients[ingredient]);
        }
        sort(p.ingredients.begin(), p.ingredients.end());
        pizzas.push_back(p);
    }

    sort(pizzas.begin(), pizzas.end(), [](const Pizza& p1, const Pizza& p2){
        return p1.ingredients.size() < p2.ingredients.size();
    });

    vector<Group> groups;
    for(ll i=0; i<T4; ++i){groups.push_back(Group(4));}
    for(ll i=0; i<T3; ++i){groups.push_back(Group(3));}
    for(ll i=0; i<T2; ++i){groups.push_back(Group(2));}

    while(M>0 && (T2>0 || T3>0 || T4>0)){
        ll group_index = -1, m_g = 0;
        for(lui i=0; i<groups.size(); ++i){
            if(groups[i].pizzas.size()!=groups[i].size){
                if(group_index==-1){
                    group_index = i;
                    m_g = inter(pizzas[M-1].ingredients, groups[i].ingredients);
                    continue;
                }
                if(inter(pizzas[M-1].ingredients, groups[i].ingredients) < m_g){
                    group_index = i;
                    m_g = inter(pizzas[M-1].ingredients, groups[i].ingredients);
                }
            }
        }
        if(group_index == -1) break;
        // cout << group_index << " index\n";

        groups[group_index].add_pizza(pizzas[M-1]);

        if(groups[group_index].pizzas.size()==groups[group_index].size){
            if(groups[group_index].size == 2) T2--;
            if(groups[group_index].size == 3) T3--;
            if(groups[group_index].size == 4) T4--;
        }
        M--;
    }
    
    // output
    ll aux=0;
    for(lui i=0; i<groups.size(); ++i){
        if(groups[i].pizzas.size()==groups[i].size){
            aux++;
        }
    }
    cout << aux << "\n";
    lui score=0;
    for(lui i=0; i<groups.size(); ++i){
        if(groups[i].pizzas.size()==groups[i].size){
            groups[i].print();
            score+=groups[i].score();
        }
    }
    cout << score << "\n";
    return 0;
}