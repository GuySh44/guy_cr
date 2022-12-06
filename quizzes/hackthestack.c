#include <stdio.h>
void func2(void *arg) {
    long f2;
    printf("Enter func2\n");
 
    /* AREA2 */
	
	*(&f2 + 2) = *((long *)arg + 2);
	*(&f2 + 3) = *((long *)arg + 3);
	
    /* AREA2 */
 
    printf("Exit func2\n");
}
void func1() {
    long f1;
    printf("Enter func1\n");
    func2(&f1);
    printf("Exit func1\n");
}
 
int main() {
    const long x=1;
    long y=5;
 
    /* AREA1 */
    
    /* PART1
    long *screw_const = (long *)&x;
    *screw_const = 1337;
    */
    
    /* PART 2
    long *not_iks = &y;
    --not_iks;
    *not_iks = 1337;
    */
    
    
    /* AREA1 */
    
    printf("x=%lu\n",x);
    func1();
 
    printf("Exit main\n");
    return 0;
} 
