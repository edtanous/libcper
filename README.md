# CPER JSON Representation & Conversion Library
This repository specifies a structure for representing UEFI CPER records (as described in UEFI Specification Appendix N) in a human-readable JSON format, in addition to a library which can readily convert back and forth between the standard CPER binary format and the specified structured JSON.

## Building
This project uses CMake (>=3.10). To build, simply run:
```
cmake .
make
```
A static library file for the parsing library will be written to `lib/`, and test executables will be written to `bin/`.

## Usage
This project comes with several binaries and libraries to help you deal with CPER binary and CPER-JSON. The first of these is `cper-convert`, which is a command line tool that can be found in `bin/`. With this, you can convert to and from CPER and CPER-JSON through the command line. An example usage scenario is below:
```
cper-convert to-cper samples/cper-json-test-arm.json --out cper.dump
cper-convert to-json cper.generated.dump
```
Another tool bundled with this repository is `cper-generate`, which is another command line tool found in `bin/`. This allows you to generate psuedo-random valid CPER records with sections of specified types for testing purposes. An example use of the program is below:
```
cper-generate --out cper.generated.dump --sections generic ia32x64
```
Help for both of these tools can be accessed through using the `--help` flag in isolation.

Finally, a static library containing symbols for converting CPER and CPER-JSON between an intermediate JSON format can be found generated in `lib/`. This contains the following useful library symbols:
```
json_object* cper_to_ir(FILE* cper_file);
void ir_to_cper(json_object* ir, FILE* out);
```

## Specification
The specification for this project can be found in `specification/`.
Specification for the CPER binary format can be found in [UEFI Specification Appendix N](https://uefi.org/sites/default/files/resources/UEFI_Spec_2_9_2021_03_18.pdf) (2021/03/18).

### Remaining Task List
- Add readable versions of the IA32/x64 processor info type GUIDs, updating specification & both conversions.
- Add remaining `cper-generate` sections for testing preparation.esting purposes.