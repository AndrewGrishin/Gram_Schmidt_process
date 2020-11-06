//
//  Gram_Schmidt_process.hpp
//  Gram_Schmidt_process
//
//  Created on 2020.07.02.
//  Copyright © 2020 All rights reserved.
//

#ifndef Gram_Schmidt_process_hpp
#define Gram_Schmidt_process_hpp
#include <iostream>
class Gram_Shmidt_process{
private:
    double** G;
    int strings;
public:
    Gram_Shmidt_process();
    void orthogonalisation();
};
#endif /* Gram_Schmidt_process_hpp */
