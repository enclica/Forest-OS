
# Configure by installing the necessary packages

# Install the necessary packages
sudo apt-get install -y build-essential
sudo apt-get install -y llvm
sudo apt-get install -y clang
sudo apt-get install -y cmake
sudo apt-get install -y libboost-all-dev
sudo apt-get install -y nasm
sudo apt-get install -y xorriso
sudo apt-get install -y grub-pc-bin

mkdir -p obj
mkdir -p logs
mkdir -p Forest
mkdir -p Forest/boot