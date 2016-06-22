import java.util.regex.Pattern;
import java.util.*;

// The types of operations available on this calculator
enum Operation {
	none,
	add,
	sub,
	mult,
	div,
	pow,
}

/* 
 * Enumeration to determine the ExpressionElement type.
 * Depending on the type, the expression is handled differently.
 */
enum ExpressionElemType {
	number,
	operation
}

class ExpressionElement {
	public ExpressionElemType type = ExpressionElemType.number;
	public Operation op = Operation.none;
	public double value = 0;

	public ExpressionElement(char[] a) {
		this.type = ExpressionElemType.number;
		double val = 0;

		boolean belowDecimal = false;
		int decimalPosition = -1;

		for(int i = 0; i < a.length; i++) {
			
			// Check for decimal points
			if(a[i] == '.') {	
				if(belowDecimal) {
					System.out.println("SYNTAX ERROR: DOUBLE DECIMAL");
					continue;
				} else {
					decimalPosition = i;
					belowDecimal = true;
					continue;
				}
			}
			
			if(!belowDecimal) {
				val = val * 10 + Character.getNumericValue(a[i]);
			} else {
				double neg10Pow = (double)(10*(i-decimalPosition));
				val = val + Character.getNumericValue(a[i])/neg10Pow;
			}
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
			case '^':
				this.op = Operation.pow;
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
			break;
		default:
			throw new Exception();
		}
		
		return value;
	}
}

//========================================================================
// STRING CALCULATOR CLASS
//========================================================================

public class StringCalculator {
	
	//================================================================
	// VARIABLES
	//================================================================

	public static final boolean DEBUG = false;

	public static final Operation[] OP_ORDER =
		{
			Operation.pow, Operation.mult,
			Operation.div, Operation.add,
			Operation.sub
		};
	
	//================================================================
	// METHODS
	//================================================================
	
	/**
	 * Main Method
	 *
	 * @param args: Arguments from command line.
	 */
	public static void main(String[] args) {
		
		System.out.print("INPUT> ");
		Scanner scanner = new Scanner(System.in);
		String input = scanner.nextLine();

		//String input = "(18*2)-60/(2+3)";

		double value = calculateCharArray(input.toCharArray());
		
		System.out.println("ANSWER: "+value);
	}
	
	/**
	 * Calculates out a character array.
	 *
	 * @param a: Char array to calculate from.
	 * @return Returns the evaluated double.
	 */
	public static double calculateCharArray(char[] a) {
		double value = 0;
		// Generate the ExpressionElement list to calculate.
		List<ExpressionElement> expressionList = generateList(a);
		
		// Debug
		if(DEBUG)
			for(ExpressionElement e : expressionList) { System.out.println("DEBUG:"+e.toString()); }
		
		try {	
			value = listCalculation(expressionList).value;
		} catch(Exception e) {
			System.out.println("THERE WAS AN ERROR.");
			return -1;
		}
		return value;
	}
	
	/**
	 * Forms a single number-type ExpressionElement by calculating a list of
	 * ExpressionElements.
	 * 
	 * @param elements: A list of ExpressionElements to calculate.
	 * @return Returns a single number type ExpressionElement.
	 */
	public static ExpressionElement listCalculation(List<ExpressionElement> elements) throws Exception {

		// Copy the old list into this new list that we will boil down to
		// a single expression element.
		List<ExpressionElement> newList = new ArrayList<ExpressionElement>(elements);
		
		// If the first element is an operation, place a 0 before it. This will
		// allow us to properly handle things like negative numbers.
		if(elements.get(0).type == ExpressionElemType.operation) {
			ExpressionElement zeroElement = new ExpressionElement(0);
			newList.add(0,zeroElement);
		}

		if(newList.size() == 2) {
			throw new Exception();
		}
		
		// Loop through every operation, in the order defined by OP_ORDER
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
				int i = 0; // Iterator
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
								System.out.println("ERROR: INVALID OPERATION.");
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
	 * Generates an ArrayList of ExpressionElements from a char array.
	 * From this, it's possible to calculate the resulting value, as each ExpressionElement
	 * has sufficient information in it to determine how to act around surrounding elements.
	 *
	 * @param a: Character array to convert
	 * @return Returns a homogenous list of ExpressionElements, which can be used to calculate
	 * the expression inputted by the user.
	 */
	public static List<ExpressionElement> generateList(char[] a) {
		List<ExpressionElement> newList = new ArrayList<ExpressionElement>();
		
		boolean grabbingSubExpression = false;
		int subExpressionStartingIndex = -1;
		
		boolean grabbingNumber = false;
		int numberStartingIndex = -1; // Index of the start of each number.
		int numberEndingIndex = -1; // Index where the last number ended off on.
		
		for(int i = 0; i < a.length; i++) {
			// Check for sub expressions first.
			if(a[i] == '(') {
				grabbingSubExpression = true;
				subExpressionStartingIndex = i+1;
				continue; // Don't check anything else, move on to next index.
			}
			else if(a[i] == ')') {
				if(grabbingSubExpression) {
					// Do a recursive call on the sub expression.
					grabbingSubExpression = false;
					char[] subExpressionCharArray = Arrays.copyOfRange(a, subExpressionStartingIndex, i);
					double subValue = calculateCharArray(subExpressionCharArray);
					newList.add(new ExpressionElement(subValue));
					continue;
				} else {
					System.out.println("SYNTAX ERROR, MISSING OPEN PAREN");
					break;
				}
			}

			if(grabbingSubExpression)
				continue; // We're grabbing a sub expression. We don't need to add anything.
			

			// Now check for actual numbers.
			boolean isNumber = Pattern.matches("[0-9]", Character.toString(a[i]));
			boolean isPoint = (a[i] == '.');

			if(i == a.length-1 && (!isNumber && !isPoint)) {
				System.out.println("SYNTAX ERROR: ENDED IN OP");
				break;
			}

			if((isNumber || isPoint) && i != a.length-1) {
				if(!grabbingNumber) {
					numberStartingIndex = i;
					grabbingNumber = true;
				}
				continue;
			} else if(grabbingNumber == true) {
				// We were grabbing a number, but now we aren't.
				grabbingNumber = false;
				
				// Did we get here because we reached the EOL or
				// because we hit something that's not a number?
				if(i == a.length-1) {
					numberEndingIndex = i+1; // it was EOL
					// Make a new array
					char[] newA = Arrays.copyOfRange(a, numberStartingIndex, numberEndingIndex);
					newList.add(new ExpressionElement(newA));
					break; // Since it was EOL, break out of loop.
				} else {
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
