GLSLC=$(which glslc)
FILE_SUFFIX=.spv

for i in *.vert; do
    $GLSLC $i -o "$i$FILE_SUFFIX"
done
for i in *.frag; do
    $GLSLC $i -o "$i$FILE_SUFFIX"
done