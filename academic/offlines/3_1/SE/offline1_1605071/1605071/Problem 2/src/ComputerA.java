public class ComputerA implements Computer {
    private String cpu1 = "CPU_A";
    private String mmu1 = "MMU_A";

    @Override
    public String getName()
    {
        return "A";
    }

    @Override
    public String getCPU() {
        return cpu1;
    }

    @Override
    public String getMMU() {
        return mmu1;
    }

    @Override
    public int getWidth() {
        return 200;
    }

    @Override
    public int getHeight() {
        return 200;
    }
}
