package clientServerSuperStructure;

/**
 * Created by Zerbs on 11.11.2016.
 */
public abstract class ByteArrayConverter {
    public static float byteArrayToFloat(byte[] floatBytes){
        return Float.intBitsToFloat(byteArrayToInt(floatBytes));
    }

    public static byte[] intToByteArray(int myInt){
        byte intBytes[] = new byte[4];
        intBytes[0] = (byte)(myInt >> 24);
        intBytes[1] = (byte)(myInt >> 16);
        intBytes[2] = (byte)(myInt >> 8);
        intBytes[3] = (byte)(myInt);

        return intBytes;
    }

    public static int byteArrayToInt(byte[] floatBytes){
        return (((floatBytes[0] << 24) & (0xFF000000)) | ((floatBytes[1] << 16) & 0x00FF0000) | ((floatBytes[2] << 8) & 0x0000FF00) | (floatBytes[3] & 0x000000FF));
    }

    public static byte[] floatToByteArray(float myFloat){
        return intToByteArray(Float.floatToIntBits(myFloat));
    }
}
