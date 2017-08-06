#! /bin/bash
#---------------------------------------------------------------------
# Script for updating HomieNode firmware via OTA
#
# Must be executed from the project scripts folder as:
#	$ ./ota-test.sh
#---------------------------------------------------------------------


#------------------------------------------------------------------------------
# main line starts here

E_SUCCESS=0         # success
E_NOARGS=65         # no arguments
E_BADPATH=66        # not running from <root>/scripts

enhanced="\e[7m"
reset="\e[0m"

#get current directory and check we are running from <root>/scripts.
#For this I just check that "src" folder exists
scripts_path="${PWD}"
root_path=$(dirname "${PWD}")
if [[ ! -e "${root_path}/src" ]]; then
    echo "Error: not running from <root>/scripts"
    exit $E_BADPATH
fi

#path for locating the new firmware
bin_path="${root_path}/.pioenvs/esp12e"

echo -e "${enhanced}Starting OTA firmware update ${reset}"
echo -e "build path: ${bin_path}"

binfile="${bin_path}/firmware.bin"

echo -e "binfile: ${binfile}"

md5sum=`md5sum $binfile | awk '{ print $1 }'`
echo -e "md5sum: ${md5sum}"
#publish MD5 checksum
#mosquitto_pub -d -h cubietruck -p 1883 -t "homie/ian_bench/\$implementation/ota/checksum" -m "$md5sum"

#send new firmware
device=thermo_ian
#device=ian_bench

base64enc=`base64 -w0 $binfile`
#mosquitto_pub -d -h cubietruck -p 1883 -t "homie/ian_bench/\$implementation/ota/firmware/$md5sum"  -l <<< "$base64enc"
mosquitto_pub -d -h cubietruck -p 1883 -t "homie/$device/\$implementation/ota/firmware/$md5sum"  -f $binfile

