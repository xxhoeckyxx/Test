public class Dictionary {
    private String[] decoded;
    private String[] encrypted;

    public Dictionary() {
        decoded = new String[]{
                "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
                "U", "V", "W", "X", "Y", "Z", "Ä", "Ö", "Ü", "0",
                "1", "2", "3", "4", "5", "6", "7", "8", "9", ".",
                ",", ":", "-", "?", ""
        };

        encrypted = new String[]{
                ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                "..-", "...-", ".--", "-..-", "-.--", "--..", ".-.-", "---.", "..--", "-----",
                ".----", "..---", "...--", "...._", ".....", "-....", "--...", "---..", "----.",
                ".-.-.-", "--..--", "---...", "-...-", "..--..", "...-.-"
        };
    }

    public String callbackDecoded(int index) {
        return decoded[index];
    }

    public String callbackEncrypted(int index) {
        return encrypted[index];
    }
}