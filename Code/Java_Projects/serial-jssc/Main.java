import jssc.SerialPortList;

public class Main {
    public static void main(String[] args) {
        String[] portNames = SerialPortList.getPortNames();
        for(int i = 0; i < portNames.length; i++){
            System.out.println(portNames[i]);
        }
    }
}
