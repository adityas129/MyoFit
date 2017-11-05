package ece155.uwaterloo.ca.lab4_202_19;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.util.Log;
import android.widget.TextView;

import java.io.PrintWriter;
import java.util.Arrays;


/**
 * Created by Aneesh on 2017-01-31.
 */
public class AccelHandler implements SensorEventListener {
    TextView output;

    float[][] history;
    int historyIndex;
    final int SMOOTHING_FACTOR = 10;

    //States and movements
    private enum states{WAIT, RISE_A, DROP_B, DETERMINED}
    private enum signatures{UP, DOWN, LEFT, RIGHT, UNKNOWN}

    private states stateX;
    private states stateY;
    private signatures signatureX;
    private signatures signatureY;

    //Expretimentally determined threshold values for left and right gestures, for FSM
    private final float[] THRESH_RIGHT = {0.6f, 2.3f};
    private final float[] THRESH_LEFT = {-0.6f, -2.3f};
    private final float[] THRESH_UP = {0.6f, 2.3f};
    private final float[] THRESH_DOWN = {-0.6f, -2.3f};

    //FSM Starts at 0 samples having been obtained initially
    private final int SAMPLEDEFAULT = 30;
    private int sampleCounter;

    private GameLoopTask myTask;

    /**
     * Constructor
     * @param outputView textview to output text to
     */
    public AccelHandler(TextView outputView, GameLoopTask myTask) {
        output = outputView;
        history = new float[100][3];
        historyIndex = 0;
        stateX = states.WAIT;
        stateY = states.WAIT;
        signatureX = signatures.UNKNOWN;
        signatureY = signatures.UNKNOWN;
        output.setText("UNDETERMINED");

        this.myTask = myTask;
    }
    /**
     * Outputs last 100 pieces of data to csv file
     */
    public void log(PrintWriter writer)
    {
        for(int row = 0;row < 100;row++)
        {
            writer.print(String.format("%f,%f,%f", history[row][0], history[row][1], history[row][2]));
            writer.println();
        }
    }

    /**
     * Updates current values in main, updates max values.
     * Keeps track of 100 most recent readings. (accelerometer only)
     * @param se event generated by sensor change
     */
    public void onSensorChanged(SensorEvent se)
    {
        //Shift all readings over by 1
        for (int row = 0; row < 99; row++)
        {
            history[row][0] = history[row+1][0];
            history[row][1] = history[row+1][1];
            history[row][2] = history[row+1][2];
        }

        //Insert filtered reading
        history[99][0] += (se.values[0] - history[99][0]) / SMOOTHING_FACTOR;
        history[99][1] += (se.values[1]- history[99][1]) / SMOOTHING_FACTOR;
        history[99][2] += (se.values[2]- history[99][2]) / SMOOTHING_FACTOR;

        //Sample has been obtained
        sampleCounter--;

        if(sampleCounter <= 0)
        {
            //If a gesture has been detected
            if((stateX == states.DETERMINED) || (stateY == states.DETERMINED))
            {
                if(signatureX == signatures.RIGHT) {
                    output.setText("RIGHT");
                    myTask.setDirection(GameLoopTask.GameDirection.RIGHT);
                }
                else if(signatureX == signatures.LEFT) {
                    output.setText("LEFT");
                    myTask.setDirection(GameLoopTask.GameDirection.LEFT);
                }
                else if(signatureY == signatures.UP) {
                    output.setText("UP");
                    myTask.setDirection(GameLoopTask.GameDirection.UP);
                }
                else if(signatureY == signatures.DOWN) {
                    output.setText("DOWN");
                    myTask.setDirection(GameLoopTask.GameDirection.DOWN);
                }
                else {
                    output.setText("N/A");
                    myTask.setDirection(GameLoopTask.GameDirection.NO_MOVEMENT);
                }
            }
            //No gesture detected but 20 samples still up
            else
            {
                output.setText("N/A");
            }

            //Reset state
            stateX = states.WAIT;
            stateY = states.WAIT;
            sampleCounter = SAMPLEDEFAULT;
        }

        //Update FSM with new data reading
        callFSM();

    }

    public void onAccuracyChanged(Sensor s, int i) {}


    /**
     * Contains implementation of Finite State Machine used to recognize gestures
     */
    public void callFSM()
    {
        double deltaX = history[99][0] - history[98][0];
        double deltaY = history[99][1] - history[98][1];

        //X-AXIS FSM Implementation
        switch(stateX)
        {
            case WAIT:
                signatureX = signatures.UNKNOWN;
                //Signal ascending (characteristic of RIGHT/UP gesture)
                if(deltaX >= THRESH_RIGHT[0])
                    stateX = states.RISE_A;

                    //Signal descending (characteristic of LEFT/DOWN gesture)
                else if(deltaX <= THRESH_LEFT[0])
                    stateX = states.DROP_B;

                break;

            case RISE_A:
                //If signal has begun to descend
                if(deltaX <= 0){
                    //If latest reading has exceeded required threshold value
                    if(history[99][0] >= THRESH_RIGHT[1]) {
                        stateX = states.DETERMINED;
                        signatureX = signatures.RIGHT;
                    }

                    else
                    {
                        stateX = states.DETERMINED;
                        signatureX = signatures.UNKNOWN;
                    }
                }
                break;

            /*case DROP_A:
                //If signal has begun to ascend
                if(deltaX >= 0){
                    if (history[99][0] <= THRESH_RIGHT[2])
                        signatureX = signatures.RIGHT;

                    stateX = states.DETERMINED;
                }
                break;*/

            /*case RISE_B:
                //If the signal has begun to descend
                if(deltaX <= 0){

                    if (history[99][0] >= THRESH_LEFT[2])
                        signatureX = signatures.LEFT;

                    stateX = states.DETERMINED;
                }
                break;*/

            case DROP_B:
                //If the signal has begun to rise
                if(deltaX >= 0){
                    //If the previous reading has exceeded the threshold value
                    if(history[99][0] <= THRESH_LEFT[1]) {
                        stateX = states.DETERMINED;
                        signatureX = signatures.LEFT;
                    }

                    else {
                        stateX = states.DETERMINED;
                        signatureX = signatures.UNKNOWN;
                    }
                }
                break;

            case DETERMINED:
                //Log.d("FSM: ", "State DETERMINED " + signatureX.toString());
                break;

            default:
                stateX = states.WAIT;
                signatureX = signatures.UNKNOWN;
                break;
        }

        //Y-AXIS FSM Implementation
        switch(stateY)
        {
            case WAIT:
                signatureY = signatures.UNKNOWN;
                //Signal ascending (characteristic of RIGHT/UP gesture)
                if(deltaY >= THRESH_UP[0])
                    stateY = states.RISE_A;

                    //Signal descending (characteristic of LEFT/DOWN gesture)
                else if(deltaY <= THRESH_DOWN[0])
                    stateY = states.DROP_B;

                break;

            case RISE_A:
                //If signal has begun to descend
                if(deltaY <= 0){
                    //If latest reading has exceeded required threshold value
                    if(history[99][1] >= THRESH_UP[1]) {
                        stateY = states.DETERMINED;
                        signatureY = signatures.UP;
                    }

                    else {
                        stateY = states.DETERMINED;
                        signatureY = signatures.UNKNOWN;
                    }
                }
                break;

           /* case DROP_A:
                //If signal has begun to ascend
                if(deltaY >= 0){
                    if (history[99][1] <= THRESH_UP[2])
                        signatureY = signatures.UP;

                    stateY = states.DETERMINED;
                }
                break;*/

            /*case RISE_B:
                //If the signal has begun to descend
                if(deltaY <= 0){

                    if (history[99][1] >= THRESH_DOWN[2])
                        signatureY = signatures.DOWN;

                    stateY = states.DETERMINED;
                }
                break;*/

            case DROP_B:
                //If the signal has begun to rise
                if(deltaY >= 0){
                    //If the previous reading has exceeded the threshold value
                    if(history[99][1] <= THRESH_DOWN[1]) {
                        stateY = states.DETERMINED;
                        signatureY = signatures.DOWN;
                    }

                    else {
                        stateY = states.DETERMINED;
                        signatureY = signatures.UNKNOWN;
                    }
                }
                break;

            case DETERMINED:
                //Log.d("FSM: ", "State DETERMINED " + signatureY.toString());
                break;

            default:
                stateY = states.WAIT;
                signatureY = signatures.UNKNOWN;
                break;
        }
    }
}