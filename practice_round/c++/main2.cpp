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

ll unio(vector<ll> &s1, vector<ll> &s2){
    vector<ll> s3;
    set_union(s1.begin(),s1.end(),s2.begin(),s2.end(), back_inserter(s3));
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

    // sort(pizzas.begin(), pizzas.end(), [](const Pizza& p1, const Pizza& p2){
    //     return p1.ingredients.size() < p2.ingredients.size();
    // });

    vector<Group> groups;
    for(ll i=0; i<T2; ++i){groups.push_back(Group(2));}
    for(ll i=0; i<T3; ++i){groups.push_back(Group(3));}
    for(ll i=0; i<T4; ++i){groups.push_back(Group(4));}

    ll g = T2+T3+T4;

    unordered_set<ll> pizzas_used;

    while(g>0){
        ll pizza_index = -1, m_g = 0;
        for(lui i=0; i<pizzas.size(); ++i){
            if(pizzas_used.count(i)!=0){
                continue;
            }
            if(pizza_index==-1){
                pizza_index = i;
                m_g = unio(pizzas[i].ingredients, groups[g-1].ingredients);
                continue;
            }
            if(unio(pizzas[i].ingredients, groups[g-1].ingredients) > m_g){
                pizza_index = i;
                m_g = unio(pizzas[i].ingredients, groups[g-1].ingredients);
            }
        }
        if(pizza_index == -1) break;
        // cout << group_index << " index\n";
        pizzas_used.insert(pizza_index);

        groups[g-1].add_pizza(pizzas[pizza_index]);

        if(groups[g-1].pizzas.size()==groups[g-1].size){
            g--;
        }
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