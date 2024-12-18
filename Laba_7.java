import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class PersonInfo {
    private String surname;    
    private String zodiacSign; 
    private String birthDate;  

    public PersonInfo(String surname, String zodiacSign, String birthDate) {
        this.surname = surname;
        this.zodiacSign = zodiacSign;
        this.birthDate = birthDate;
    }

    public String getSurname() {
        return surname;
    }

    public String getZodiacSign() {
        return zodiacSign;
    }

    public String getBirthDate() {
        return birthDate;
    }

    public int getBirthMonth() {
        return Integer.parseInt(birthDate.split("\\.")[1]);
    }

    @Override
    public String toString() {
        return "Фамилия: " + surname + ", Знак зодиака: " + zodiacSign + ", Дата рождения: " + birthDate;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<PersonInfo> people = new ArrayList<>();

        people.add(new PersonInfo("Иванов", "Рыбы", "15.03.1990"));
        people.add(new PersonInfo("Петров", "Весы", "12.10.1985"));
        people.add(new PersonInfo("Сидоров", "Лев", "28.07.1995"));
        people.add(new PersonInfo("Кузнецов", "Козерог", "05.01.2000"));

        System.out.print("Введите номер месяца (1-12): ");
        int month = scanner.nextInt();

        // Фильтрация людей по указанному месяцу
        List<PersonInfo> filteredPeople = new ArrayList<>();
        for (PersonInfo person : people) {
            if (person.getBirthMonth() == month) {
                filteredPeople.add(person);
            }
        }

        if (filteredPeople.isEmpty()) {
            System.out.println("Людей, родившихся в указанном месяце, нет.");
        } else {
            System.out.println("Люди, родившиеся в указанном месяце:");
            for (PersonInfo person : filteredPeople) {
                System.out.println(person);
            }

            try (BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"))) {
                for (PersonInfo person : filteredPeople) {
                    writer.write(person.toString());
                    writer.newLine();
                }
                System.out.println("Информация записана в файл output.txt.");
            } catch (IOException e) {
                System.out.println("Ошибка при записи в файл: " + e.getMessage());
            }
        }
    }
}
