import java.io.FileWriter;
import java.io.IOException;

public class allData_ExamSchedule {
    public static void main(String[] args) throws IOException {
        String[] dataset = {"car-s-91", "car-f-92", "kfu-s-93", "tre-s-92", "yor-f-83"};

        FileWriter myWriter = new FileWriter("1605071report.txt");

        /*for(int i=0; i<crsList.size(); i++)
        {
            //System.out.println(crsList.get(i).getU() + " - " + crsList.get(i).getColor());
            //System.out.println("here");
            myWriter.write(crsList.get(i).getU() + " " + crsList.get(i).getColor() + "\n");
        }*/

        myWriter.write("\nLargest_Degree_min_slot ; initial_penalty ; Kempe_chain_penalty ; Pair_swap_penalty");
        System.out.print("\nLargest_Degree_min_slot ; initial_penalty ; Kempe_chain_penalty ; Pair_swap_penalty");
        myWriter.write("\t\t\t|\t");
        System.out.print("\t\t\t|\t");
        myWriter.write("Dsatur_min_slot ; initial_penalty ; Kempe_chain_penalty ; Pair_swap_penalty\n\n");
        System.out.print("Dsatur_min_slot ; initial_penalty ; Kempe_chain_penalty ; Pair_swap_penalty\n");
        myWriter.write("--------------------------------------------------------------------------------------------\n");
        System.out.println("--------------------------------------------------------------------------------------------------------------");

        for(int i=0; i<dataset.length; i++)
        {
            myWriter.write(dataset[i]);
            myWriter.write(":\t");
            System.out.print(dataset[i] + ": ");
            String stuFile = dataset[i] + ".stu";
            //System.out.print(stuFile);
            //System.out.print(" - ");
            String crsFile = dataset[i] + ".crs";
            //System.out.print(crsFile);
            //System.out.println();
            String solFile = dataset[i] + "LD.sol";

            new_LDExamSchedule es = new new_LDExamSchedule();
            String result = es.examScheduler(stuFile, crsFile, solFile);

            myWriter.write("( ");
            myWriter.write(result);
            myWriter.write((" )"));
            //myWriter.write("\n");
            System.out.print("( ");
            System.out.print(result);
            System.out.print(" )");

            myWriter.write("\t|\t");
            System.out.print("\t\t\t\t\t\t\t|\t");

            String solFiled = dataset[i] + "DS.sol";

            new_DSaturExamSchedule esd = new new_DSaturExamSchedule();
            String resultd = esd.examScheduler(stuFile, crsFile, solFiled);
            myWriter.write("( ");
            myWriter.write(resultd);
            myWriter.write((" )"));
            myWriter.write("\n");

            System.out.print("( ");
            System.out.print(resultd);
            System.out.println(" )");

            myWriter.write("------------------------------------------------------------------------------------------------------------------------------------------------\n");
            System.out.println("--------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        }

        //System.out.println();
        //System.out.println();

        /*myWriter.write("\n\nDsatur min slot + initial penalty + Kempe chain penalty + Pair swap penalty\n\n");
        System.out.println("Dsatur min slot + initial penalty + Kempe chain penalty + Pair swap penalty\n");

        for(int i=0; i<dataset.length; i++)
        {
            myWriter.write(dataset[i]);
            myWriter.write(": ");
            System.out.print(dataset[i] + ": ");
            String stuFile = dataset[i] + ".stu";
            //System.out.print(stuFile);
            //System.out.print(" - ");
            String crsFile = dataset[i] + ".crs";
            //System.out.print(crsFile);
            //System.out.println();
            String solFile = dataset[i] + "DS.sol";

            new_DSaturExamSchedule es = new new_DSaturExamSchedule();
            String result = es.examScheduler(stuFile, crsFile, solFile);
            myWriter.write(result);
            myWriter.write("\n");
            System.out.println(result);
            myWriter.write("--------------------------------------------------------------------------------------------\n");
            System.out.println("----------");
        }*/

        myWriter.close();
    }
}
