package my.test;
import java.util.Arrays;
import java.util.List;

import com.sun.jna.Structure;

/**
 * 
 */

/**
 * @author vaibhav
 *
 */
public class TableEvent extends Structure
{
	/* All member variables has to be public to use jna */
	public TableEvent()
	{
	}
	
	public long mtype;
	
	public String topic;
	
	public String data;

	@Override
	protected List getFieldOrder()
	{
		return Arrays.asList(new String[]{"mtype", "topic", "data"});
	}
}
