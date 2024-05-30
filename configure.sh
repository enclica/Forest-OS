
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
sudo apt-get install -y libc6-dev

mkdir -p obj
mkdir -p logs

mkdir -p iso/boot/grub
mkdir -p iso/themes/
mkdir -p iso/themes/default
mkdir -p iso/themes/default/icons
mkdir -p iso/themes/default/icons/16x16
mkdir -p iso/themes/default/icons/32x32
mkdir -p iso/themes/default/icons/48x48
mkdir -p iso/themes/default/icons/64x64
mkdir -p iso/themes/default/sounds/



cp -r Sounds/* iso/themes/default/sounds/

# Copy the grub.cfg file to the iso/boot/grub directory if the directory exists
if [ -d "iso/boot/grub" ]; then

    if [ -f "Grub/grub.cfg" ]; then
        cp Grub/grub.cfg iso/boot/grub/grub.cfg
    else
        echo "Grub/grub.cfg file does not exist"
    fi
fi
