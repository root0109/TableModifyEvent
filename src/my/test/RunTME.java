/**
 * 
 */
package my.test;

/**
 * @author vaibhav
 *
 */
public class RunTME
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		TableEventReader tableEventReader = TableEventReader.instance; 
		try
		{
			//Run for 15 minutes
			Thread.sleep(15 * 60 * 60);
		}
		catch (InterruptedException e)
		{
			e.printStackTrace();
		}
		tableEventReader.stop();
	}
}
