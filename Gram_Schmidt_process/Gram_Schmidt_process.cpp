#include "Gram_Schmidt_process.hpp"
#include <vector>

namespace spf{
    // lambda function for X_VECTOR * G_MATRIX * Y_VECTOR
    const auto scalarMultWithGramMatrix = [](double* x, double* y, double** G, int str) -> double{
        double result(0.0);
        // multiplication of x_vector * G_matrix * y_vector
        for (int i = 0; i < str; i++){
            for (int j = 0; j < str; j++){
                result += (*(x + j)) * (*(*(G + j) + i)) * (*(y + i)); // x[i] * G[j][i] * y[j]
            }
        }
        return result;
    };
    // lambda function to INPUT new VECTOR from user and ADD it into STACK ARRAY-VECTOR
    const auto inputNewVector = [](std::vector<double*>&stack, int str){
        double* a = new double[str] {0};
        for (int i = 0; i < str; i++) std::cin >> *(a + i);
        stack.push_back(a);
    };
    // lambda function to SUM TWO VECTORS
    const auto sumVectors = [](double* a, double* b, int str) -> double*{
        for (int i = 0; i < str; i++){ *(a + i) += *(b + i); } return a;
    };
    // lambda function to MULT VECTOR BY NUMBER
    const auto multVectorByNymber = [](double* a, double number, int str) -> double*{
        for (int i = 0; i < str; i++) *(a + i) *= number; return a;
    };
}

Gram_Shmidt_process::Gram_Shmidt_process(){
    // ask for number if STRINGS and COLOMNS in Gram Matrix (hint: they MUST be equal to each other)
    std::cout << "Input number of strings and colomns in Gram matrix (MUST be eql): "; std::cin >> this->strings;
    // allocate memory for Gram Matrix
    G = new double*[this->strings]; for (int i = 0; i < this->strings; i++) *(G + i) = new double[this->strings];
    // Ask to input and input Gram Matrix
    std::cout << "Input Gram Matrix." << std::endl;
    for (int i = 0; i < this->strings; i++){ for (int j = 0; j < this->strings; j++){ std::cin >> *(*(G + i) + j); } }
    std::cout << std::endl;
}

void Gram_Shmidt_process::orthogonalisation(){
    // vector to SAVE INPUT (vectors to orth)
    std::vector<double*>stack;
    // ortogonalisation loop (input one, orth one)
    while (true){
        //check if it is useless to continue the process of ortho, beacuse when we are out of the size of our demention, then all orthos will be zeros
        if ((int)stack.size() + 1 > this->strings) {
            // clear stack
            stack = {};
            std::cout << std::endl;
            std::cout << "The process has been started again, because the number of vectors was already " << this->strings << "." << std::endl << std::endl;
        }
        // input new vector
        std::cout << "Input vector " << stack.size() + 1 << ": ";
        spf::inputNewVector(stack, strings);
        // check to break the loop (last Vector must have 0 length) (lambda function to check, if all coordinates are ZER0)
        auto checker = [](double* na, int str) -> bool{
            for (int i = 0; i < str; i++) if (*(na + i) != 0) return false;
            return true;
        };
        if (checker(stack[stack.size() - 1], this->strings)) break;
        // OUTPUT LAST INPUTED VECTOR
        std::cout << "{ "; for (int i = 0; i < this->strings; i++){ std::cout << stack[stack.size() - 1][i] << " "; } std::cout << "}";
        // orthogonalisation
        double* b = new double[this->strings]{0};
        b = stack[stack.size() - 1];
        for (int i = 0; i < stack.size() - 1; i++){
            b = spf::sumVectors(b, spf::multVectorByNymber(stack[i], -1 * spf::scalarMultWithGramMatrix(stack[stack.size() - 1], stack[i], this->G, this->strings) / spf::scalarMultWithGramMatrix(stack[i], stack[i], this->G, this->strings),this->strings), this->strings);
        }
        // output vectors B[i] (final one - after orthogonalisation)
        std::cout << " -> { "; for (int i = 0; i < this->strings; i++){ std::cout << *(b + i) << " "; } std::cout << "}" << std::endl << std::endl;
    }
}
