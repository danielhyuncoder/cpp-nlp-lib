#include <iostream>
#include "./include/NLP.h"


int main()
{
    
    

    lib::NLP* nlp = new lib::NLP(lib::importFromJSON("./example_data/positive_negative_model_data.json", 2));
    
    nlp->fit(10);
    int p = nlp->predict("asvhik is plagued by doubt");
     
    std::cout << p << std::endl;
    
    
}