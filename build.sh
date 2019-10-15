emcc main.cpp -o target.wasm -std=c++17 -s STANDALONE_WASM -s EXPORT_ALL=0 -s EXPORTED_FUNCTIONS="['_add', '_set', '_getData', '_concat', '_contains']"
