#define ANALOG_DOWN_VALUE  (50)
#define MAX_JITTER_COUNT   (100)
#define TRUE               (1)
#define FALSE              (0)

#define BOX_WRONG_FLAG   (0)
#define BOX_RIGHT_FLAG   (1)

#define BOX_UP_FLAG      (2)
#define BOX_DOWN_FLAG    (3)

#define A_PIN            (4)
#define D_PIN            (5)

#define GAME_NULL        (6)
#define GAME_START       (7)
#define GAME_SUCESS      (8)
#define GAME_RIGHT_BOX   (9)
#define GAME_WRONG_BOX   (10)

struct box {
    int pin;
    int pin_flag;
    int right_wrong_flag;
    int up_down_flag;
    struct box* next;
    struct box* next_all;
};

struct box a1 = {15, A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, NULL};
struct box a2 = {14, A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &a1};
struct box a3 = {13, A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &a2};
struct box a4 = {12, A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &a3};
struct box a5 = {11, A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &a4};
struct box a6 = {10, A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &a5};
struct box a7 = {9,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &a6};
struct box a8 = {8,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &a7};

struct box b1 = {7,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &a8};
struct box b2 = {6,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &b1};
struct box b3 = {5,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &b2};
struct box b4 = {4,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &b3};
struct box b5 = {3,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &b4};
struct box b6 = {2,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &b5};
struct box b7 = {1,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &b6};
struct box b8 = {0,  A_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &b7};

struct box c1 = {23, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &b8};
struct box c2 = {22, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &c1};
struct box c3 = {21, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &c2};
struct box c4 = {20, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &c3};
struct box c5 = {19, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &c4};
struct box c6 = {18, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &c5};
struct box c7 = {17, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &c6};
struct box c8 = {16, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &c7};

struct box d1 = {6,  D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &c8};
struct box d2 = {7,  D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &d1};
struct box d3 = {8,  D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &d2};
struct box d4 = {9,  D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &d3};
struct box d5 = {10, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &d4};
struct box d6 = {11, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &d5};
struct box d7 = {12, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &d6};
struct box d8 = {13, D_PIN, BOX_WRONG_FLAG, BOX_UP_FLAG, NULL, &d7};

static inline void box_copy(struct box* dst, const struct box* src)
{
    if(NULL==src) {
        return ;
    }
    memcpy(dst, src, sizeof(struct box));
}

static int is_box_down(const struct box* box)
{
    if(box->pin_flag == D_PIN) {
        return (LOW == digitalRead(box->pin))? TRUE: FALSE;
    }
    else {
        return (ANALOG_DOWN_VALUE > analogRead(box->pin))? TRUE: FALSE;
    }
}

static void update_box_up_down_flag(void)
{
    struct box* tmp = &d8;
    while(NULL != tmp->next_all) {
        if(TRUE == is_box_down(tmp)) {
            tmp->up_down_flag = BOX_DOWN_FLAG;
        }
        tmp = tmp->next_all;
    }
}

static int get_all_down_pin_count(void)
{
    int down_count = 0;
    struct box* tmp = &d8;
    while(NULL != tmp->next_all) {
        if(BOX_DOWN_FLAG == tmp->up_down_flag) {
            down_count++;
        }
        tmp = tmp->next_all;
    }

    return down_count;
}

static struct box* find_first_down_box(void)
{
    struct box* tmp = &d8;
    while(NULL != tmp->next_all) {
        if(BOX_DOWN_FLAG == tmp->up_down_flag) {
            return tmp;
        }
        tmp = tmp->next_all;
    }
}

static struct box* read_boxs(void)
{
    int box_num = 0;
    update_box_up_down_flag();
    box_num = get_all_down_pin_count();

    if(1 == box_num) {
        return find_first_down_box();
    }
    else if (2 == box_num) {
        /* cause I link all boxes from d8 to a8,
            so if there are two down boxes, still find first down box from d8 to a8
        */
        return find_first_down_box();
    }
    else {
        return NULL;
    }

}

int is_game_over(const struct box* pre, const struct box* now){
	static int jitter_count = 0;
	if(NULL == pre){ /* first down box */
		return (now->right_wrong_flag)? GAME_RIGHT_BOX: GAME_WRONG_BOX;
	}
	else if(NULL == now){ /* may be jitter, may be gamer is go out */
		jitter_count ++;
		if(jitter_count < MAX_JITTER_COUNT){
			return GAME_NULL;
		}
		else{
			jitter_count = 0;
			return GAME_START;
		}
	}
	else if(pre == now){ /* stand on one box, no move */
		return (now->right_wrong_flag)? GAME_NULL: GAME_WRONG_BOX;
	}
	else {
		return (pre->next == now)? GAME_RIGHT_BOX: GAME_WRONG_BOX;
	}
}

static void do_game_sucess(void){
	;
}

static void do_game_right_box(void){
	;
}

static void do_game_start(void){
	;
}

static inline void box_pin_setup(struct box* box)
{
    if(box->pin_flag == D_PIN) {
        pinMode(box->pin, INPUT);
    }
}

void setup()
{
    struct box* tmp = &d8;
    while(NULL != tmp->next_all) {
        box_pin_setup(tmp);
        tmp = tmp->next_all;
    }
}

void loop()
{
restart:
    struct box* now_box = NULL;
    struct box* pre_box = NULL;
    int g_flag = GAME_START;

    box_copy(pre_box, now_box);
    now_box = read_boxs();
    g_flag = is_game_over(pre_box, now_box);

    if(g_flag == GAME_SUCESS) {
        do_game_sucess();
    }
    else if(g_flag == GAME_RIGHT_BOX) {
        do_game_right_box();
    }
    else if(g_flag == GAME_WRONG_BOX) {
        goto restart;
    }
    else if(g_flag == GAME_START){
        do_game_start();
    }
	else {
		;
	}
}
