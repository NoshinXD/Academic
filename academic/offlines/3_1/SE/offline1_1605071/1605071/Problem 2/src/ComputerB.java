public class ComputerB implements Computer {
    private String cpu2 = "CPU_B";
    private String mmu2 = "MMU_B";

    @Override
    public String getName()
    {
        return "B";
    }

    @Override
    public String getCPU() {
        return cpu2;
    }

    @Override
    public String getMMU() {
        return mmu2;
    }

    @Override
    public int getWidth() {
        return 350;
    }

    @Override
    public int getHeight() {
        return 250;
    }
}
