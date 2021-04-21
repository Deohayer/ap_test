git clone https://github.com/deohayer/ap_test.git  
cd ap_test  
mkdir build && cd build  
cmake ../  
cmake --build ./  
./ap_validate --gtest_repeat=200 --gtest_brief=1 --gtest_break_on_failure
