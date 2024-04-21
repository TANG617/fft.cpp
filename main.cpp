#include <iostream>
#include <cmath>
#include <chrono>
#include<fstream>

#define N 1024
#define PI 3.14159265359

class complex_double_t{
public:
    double real,imag;
    complex_double_t():real(0),imag(0){}
    explicit complex_double_t(int real):real(real),imag(0){}
    complex_double_t(double real,double imag):real(real),imag(imag){}

    complex_double_t operator+(const complex_double_t & cdouble_a) const{
        complex_double_t cdouble_res;
        cdouble_res.real = this->real + cdouble_a.real;
        cdouble_res.imag = this->imag + cdouble_a.imag;
        return cdouble_res;
    }

    complex_double_t operator-(const complex_double_t & cdouble_a) const{
        complex_double_t cdouble_res;
        cdouble_res.real = this->real - cdouble_a.real;
        cdouble_res.imag = this->imag - cdouble_a.imag;
        return cdouble_res;
    }

    complex_double_t operator*(const complex_double_t & cdouble_a) const{
        complex_double_t cdouble_res;
        cdouble_res.real = this->real * cdouble_a.real - this->imag * cdouble_a.imag;
        cdouble_res.imag = this->imag * cdouble_a.real + this->real * cdouble_a.imag;
        return cdouble_res;
    }
    void input(){
        std::cin>>real>>imag;
    }

    void output(){
//        std::cout<<real<<"+"<<imag<<"j"<<" ";
        imag >= 0? printf("%.4f+%.4fi,",real,imag):printf("%.4f%.4fi,",real,imag);
    }

    double ampl(){
        return sqrt(pow(real,2)+pow(imag,2));
    }

};

class signal_t{
public:
    complex_double_t signal[N];
    signal_t(){}
    explicit signal_t(complex_double_t init_signal[N]) {
        std::copy(init_signal, init_signal + N, signal);
    }
    void input(){
        for (auto & i : signal) {
            i.input();
        }
    }
    void output(){
        for (auto & i : signal) {
            i.output();
        }
        std::cout<<std::endl;
    }

    int get_index(int org_i){
        int digital = log2(N);
        int tar_i = 0;
        for(int i=0;i<digital;i++){
            tar_i += (org_i%2) * pow(2,digital-i-1);
            org_i = org_i/2;
        }
        return tar_i;
    }

    void re_order(){
        for (int org_i = 0; org_i < N; ++org_i) {
            int tar_i = get_index(org_i);
            if (tar_i > org_i) { // 只在目标索引大于当前索引时交换，避免重复交换
                std::swap(signal[org_i], signal[tar_i]);
            }
        }

    }
};


class stage_t{
public:
    int n_stage;
    int gap;
    int num_cluster, num_signal_each;
    signal_t in;
    signal_t out;

    complex_double_t butterflyKnock_out_0,butterflyKnock_out_1;

    stage_t(signal_t in,int n_stage): in(in),n_stage(n_stage){
        gap = (int)pow(2,n_stage - 1);
        num_signal_each = pow(2,n_stage);
        num_cluster = N / num_signal_each;

        for(int n_cluster = 0; n_cluster < num_cluster ; n_cluster++){
            for (int n_signal = 0; n_signal < num_signal_each/2; ++n_signal) {
                butterfly_knock(in.signal[n_signal+n_cluster*num_signal_each],in.signal[n_signal+n_cluster*num_signal_each+gap],n_signal);
                out.signal[n_signal+n_cluster*num_signal_each] = butterflyKnock_out_0;
                out.signal[n_signal+n_cluster*num_signal_each+gap] = butterflyKnock_out_1;
            }
        }
//        out.output();
    }

    complex_double_t w(int n, int i){ //W_n ^i
        double rad = -2 * PI * i / n;
        return {cos(rad),sin(rad)};
    }

    void butterfly_knock(complex_double_t in_0, complex_double_t in_1, int n_cluster){
        butterflyKnock_out_0 = in_0 + in_1 * w(pow(2,n_stage),n_cluster);
        butterflyKnock_out_1 = in_0 - in_1 * w(pow(2,n_stage),n_cluster);
    }

};


class fft{
public:
    signal_t out;
    int num_stage;
    fft(signal_t in):out(in){
        num_stage = log2(N);
        for (int n_stage = 1; n_stage <= num_stage; ++n_stage) {
            stage_t cur_stage(out,n_stage);
            out = cur_stage.out;
        }
    }

};

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    int maxcycle = 10000;
    for(int i=0;i<maxcycle;i++)
    {
        freopen("/Users/timli/CLionProjects/FFT/X.txt", "r", stdin);
        complex_double_t x[N] ;
        auto s_x = signal_t(x);
        s_x.input();
        s_x.re_order();
        auto s_y = fft(s_x);
//        freopen("/Users/timli/CLionProjects/FFT/Y_CPP.txt", "w", stdout);
//        s_y.out.output();
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time each: " << elapsed.count()/maxcycle*1000000 << " us\n";
    std::cout << "Elapsed time total: " << elapsed.count() << " s\n";
//    return 0;

}