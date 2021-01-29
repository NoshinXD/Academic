import java.util.Random;
import java.util.Scanner;

public abstract class Person {
    protected ExamControllerOffice mediator;
    public int ID;

    public Person(ExamControllerOffice _mediator) {
        mediator = _mediator;
    }

}
