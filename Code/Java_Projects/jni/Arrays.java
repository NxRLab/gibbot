public class Arrays {
    // make proper modifications to this method to return myarr in arrays.cpp
    public static double[] GetArrayFromC()
    {
        double[] r = {100, 200, 300, 400, 500, 600, 700};
        return r;
    }


    // use main to test your JNI code
    public static void main(String args[]) 
    {
        double[] arr = Arrays.GetArrayFromC();

        System.out.println("The values of arr are:");
        for(int i = 0; i < arr.length; i++) {
            System.out.println("arr[i] = " + arr[i]);
        }
    }
}
