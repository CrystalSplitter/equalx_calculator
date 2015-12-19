import java.util.regex.Pattern;
import java.util.*;

enum Operation {
	none,
	add,
	sub,
	mult,
	div,
	pow,
}

enum ExpressionElemType {
	number,
	operation,
	openparen,
	closeparen
}

class ExpressionElement {
	public ExpressionElemType type = ExpressionElemType.number;
	public Operation op = Operation.none;
	public double value = 0;
	
	public ExpressionElement(char[] a) {
		this.type = ExpressionElemType.number;
		float val = 0;
		for(int i = 0; i < a.length; i++) {
			//System.out.println(Character.toString(a[i]));
			val = val * 10 + Character.getNumericValue(a[i]);
		}
		this.value = val;
	}
	
	public ExpressionElement(char c) {
		boolean isNumber = Pattern.matches("[0-9]", Character.toString(c));
		
		if(isNumber) {
			this.type = ExpressionElemType.number;
			this.value = Character.getNumericValue(c);
		} else {
			this.type = ExpressionElemType.operation;
			switch(c) {
			case '+':
				this.op = Operation.add;
				break;
			case '-':
				this.op = Operation.sub;
				break;
			case '*':
				this.op = Operation.mult;
				break;
			case '/':
				this.op = Operation.div;
				break;
			default:
				this.op = Operation.none;
				System.out.println("WARNING: Interpreting number as Operation");
				break;
			}
		}
	}
	
	public ExpressionElement(double val) {
		this.type = ExpressionElemType.number;
		this.value = val;
	}
	
	public String toString() {
		String s;
		
		if(type == ExpressionElemType.number) {
			s = String.valueOf(this.value);
		}
		else {
			s = op.toString();
		}
		
		return s;
	}
	
	public double calc(ExpressionElement before, ExpressionElement after) throws Exception {
		if(this.type != ExpressionElemType.operation
				|| before.type != ExpressionElemType.number
				|| after.type != ExpressionElemType.number) {
				throw new Exception();
		}
		
		double value;
		
		switch(this.op) {
		case add:
			value = before.value + after.value;
			break;
		case sub:
			value = before.value - after.value;
			break;
		case mult:
			value = before.value * after.value;
			break;
		case div:
			value = before.value / after.value;
			break;
		case pow:
			value = Math.pow(before.value, after.value);
		default:
			throw new Exception();
		}
		
		return value;
	}
}

//========================================================================
// STRING CALCULATOR
//========================================================================

public class StringCalculator {
	
	public static final Operation[] OP_ORDER =
		{Operation.pow, Operation.mult,
			Operation.div, Operation.add,
			Operation.sub};
	
	public static void main(String[] args) {
		
		String input = "60*3-8";
		double value = calculateCharArray(input.toCharArray());
		
		System.out.println(value);
		
	}
	
	public static double calculateCharArray(char[] a) {
		double value = 0;
		// Generate the
		List<ExpressionElement> expressionList = generateList(a);
		for(ExpressionElement e : expressionList) { System.out.println(e.toString()); }
		
		value = listCalculation(expressionList).value;
		
		return value;
	}
	
	public static ExpressionElement listCalculation(List<ExpressionElement> elements) {
		List<ExpressionElement> newList = new ArrayList<ExpressionElement>(elements);
		
		if(elements.get(0).type == ExpressionElemType.operation) {
			ExpressionElement zeroElement = new ExpressionElement(0);
			newList.add(0,zeroElement);
		}
		
		for(Operation e : OP_ORDER) {
			int opCount = 0; // Number of this type of operations in expression.
			
			for(int q = 0; q < newList.size(); q++) {
				if(newList.get(q).type == ExpressionElemType.operation) {
					if(newList.get(q).op == e) {
						opCount++;
					}
				}
			}
			
			while(opCount > 0) {
				int i = 0;
				while(i < newList.size()-2) {
					ExpressionElement elem = newList.get(i+1);
					if(elem.type == ExpressionElemType.operation) {
						if(elem.op == e) {
							try {
								double eval = elem.calc(newList.get(i), newList.get(i+2));
								newList.set(i, new ExpressionElement(eval));
								newList.remove(i+2);
								newList.remove(i+1);
							} catch(Exception e1) {
								System.out.println("Error: Not a valid operation.");
								e1.printStackTrace();
							}
							opCount--;
						}
					}
					i++;
				}
			}
		}
		return newList.get(0);
	}
	
	/**
	 * 
	 * @param a: Character array to convert
	 * @return Returns a homogenous list of ExpressionElements, which can be used to calculate
	 * the expression inputted by the user.
	 */
	public static List<ExpressionElement> generateList(char[] a) {
		List<ExpressionElement> newList = new ArrayList<ExpressionElement>();
		
		boolean grabbingNumber = false;
		int numberStartingIndex = -1; // Index of the start of each number.
		int numberEndingIndex = -1; // Index where the last number ended off on.
		
		for(int i = 0; i < a.length; i++) {
			
			boolean isNumber = Pattern.matches("[0-9]", Character.toString(a[i]));
			boolean isPoint = (a[i] == '.');
			
			if((isNumber || isPoint) && i != a.length-1) {
				if(!grabbingNumber)	{
					numberStartingIndex = i;
					grabbingNumber = true;
				}
				continue;
			}
			else if(grabbingNumber == true) {
				// We were grabbing a number, but now we aren't.
				grabbingNumber = false;
				
				// Did we get here because we reached the EOL or
				// because we hit something that's not a number?
				if(i == a.length-1)	{
					numberEndingIndex = i+1; // it was EOL
					// Make a new array
					char[] newA = Arrays.copyOfRange(a, numberStartingIndex, numberEndingIndex);
					newList.add(new ExpressionElement(newA));
					break; // Since it was EOL, break out of loop.
				}
				else {
					numberEndingIndex = i; // it wasn't a number
					// Make a new array
					char[] newA = Arrays.copyOfRange(a, numberStartingIndex, numberEndingIndex);
					newList.add(new ExpressionElement(newA));
				}
			}
			
			// Since it's not a number, consider it an operation.
			newList.add(new ExpressionElement(a[i]));
		}
		
		// Return the newly created ExpressionElement list
		return newList;
	}
}
