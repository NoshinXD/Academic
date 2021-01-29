public class ComputerC implements Computer {
    private String cpu3 = "CPU_C";
    private String mmu3 = "MMU_C";

    @Override
    public String getName() {
        return "C";
    }

    @Override
    public String getCPU() {
        return cpu3;
    }

    @Override
    public String getMMU() {
        return mmu3;
    }

    @Override
    public int getWidth() {
        return 550;
    }

    @Override
    public int getHeight() {
        return 430;
    }
}
