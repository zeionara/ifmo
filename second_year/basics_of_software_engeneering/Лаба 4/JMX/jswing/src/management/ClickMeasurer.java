package management;

public class ClickMeasurer implements ClickMeasurerMBean {
    private int countOfClicks = 0;
    private int averageInterval = 0;

    private int allIntervals = 0;
    private long lastTimeOfClick = 0;

    @Override
    public void areaClicked() {
        if (lastTimeOfClick == 0){
            lastTimeOfClick = System.currentTimeMillis();
            return;
        }
        long currentTimeOfClick = System.currentTimeMillis();
        allIntervals += (currentTimeOfClick - lastTimeOfClick);
        countOfClicks += 1;
        averageInterval = allIntervals /countOfClicks;
        lastTimeOfClick = currentTimeOfClick;
    }

    @Override
    public double getAverageInterval() {
        return averageInterval;
    }

    @Override
    public int getCountOfClicks() {
        return countOfClicks;
    }
}
