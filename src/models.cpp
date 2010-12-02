/****************************************************************************
 *  Copyright (C) 2005-2010  Reed A. Cartwright, PhD <reed@scit.us>         *
 *                                                                          *
 *  This program is free software: you can redistribute it and/or modify    *
 *  it under the terms of the GNU General Public License as published by    *
 *  the Free Software Foundation, either version 3 of the License, or       *
 *  (at your option) any later version.                                     *
 *                                                                          *
 *  This program is distributed in the hope that it will be useful,         *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *  GNU General Public License for more details.                            *
 *                                                                          *
 *  You should have received a copy of the GNU General Public License       *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

#include "ngila.h"
#include "models.h"

#include <limits>
#include <iomanip>

#ifdef USE_GSL_ZETA
#include <gsl/gsl_sf_zeta.h>
inline double log_zeta(double z) { return log(gsl_sf_zeta(z)); }
#else
double log_zeta(double z) {
	// spline interpolation of 
	// y = log((z-1)*zeta(z)) for z = seq(1,10.1,0.1)
	static double y[92] = {
		0.00000000000000000e+00, 5.68007048928620834e-02, 1.11824418961510755e-01, 1.65162481245235387e-01,
		2.16899224977457172e-01, 2.67112722170841699e-01, 3.15875427900892403e-01, 3.63254740373157525e-01,
		4.09313489900198446e-01, 4.54110367565164985e-01, 4.97700302470745981e-01, 5.40134794961248610e-01,
		5.81462211982759714e-01, 6.21728049750888800e-01, 6.60975168080968012e-01, 6.99244000065426419e-01,
		7.36572740229037959e-01, 7.72997513832677563e-01, 8.08552529612340476e-01, 8.43270217918634102e-01,
		8.77181355951436870e-01, 9.10315181555988784e-01, 9.42699496853069863e-01, 9.74360762811215531e-01,
		1.00532418572836546e+00, 1.03561379646993168e+00, 1.06525252320689856e+00, 1.09426225830844959e+00,
		1.12266391996660997e+00, 1.15047750906370894e+00, 1.17772216173544519e+00, 1.20441619803187527e+00,
		1.23057716703450559e+00, 1.25622188874908414e+00, 1.28136649305977168e+00, 1.30602645600060807e+00,
		1.33021663357389319e+00, 1.35395129332193020e+00, 1.37724414383803273e+00, 1.40010836238450520e+00,
		1.42255662076911871e+00, 1.44460110961722821e+00, 1.46625356116381989e+00, 1.48752527067832974e+00,
		1.50842711662481577e+00, 1.52896957965086511e+00, 1.54916276049037749e+00, 1.56901639685795402e+00,
		1.58853987940593444e+00, 1.60774226680911636e+00, 1.62663230003675863e+00, 1.64521841586655548e+00,
		1.66350875969082224e+00, 1.68151119766111612e+00, 1.69923332821384077e+00, 1.71668249301607734e+00,
		1.73386578736785757e+00, 1.75079007009433818e+00, 1.76746197295883389e+00, 1.78388790962537036e+00,
		1.80007408419733039e+00, 1.81602649935684246e+00, 1.83175096412782179e+00, 1.84725310128395459e+00,
		1.86253835442144466e+00, 1.87761199471499252e+00, 1.89247912737422341e+00, 1.90714469781663887e+00,
		1.92161349757210820e+00, 1.93589016993294716e+00, 1.94997921536272623e+00, 1.96388499667612382e+00,
		1.97761174400136919e+00, 1.99116355953612101e+00, 2.00454442210694284e+00, 2.01775819154196467e+00,
		2.03080861286571279e+00, 2.04369932032459678e+00, 2.05643384125103657e+00, 2.06901559977375671e+00,
		2.08144792038136428e+00, 2.09373403134591785e+00, 2.10587706801283314e+00, 2.11788007596312688e+00,
		2.12974601405368036e+00, 2.14147775734089807e+00, 2.15307809989286270e+00, 2.16454975749481671e+00,
		2.17589537025256385e+00, 2.18711750509813818e+00, 2.19821865820188833e+00, 2.20920125729490113e+00
	};
	static double b[92] = {
		5.77198067017487992e-01, 5.58968262571901242e-01, 5.41661451540230487e-01, 5.25239221838376791e-01,
		5.09625841584655737e-01, 4.94764639591190325e-01, 4.80601687753637097e-01, 4.67089155463733474e-01,
		4.54183550370610756e-01, 4.41845458814050907e-01, 4.30038991489612388e-01, 4.18731397110005898e-01,
		4.07892705430773550e-01, 3.97495424856108670e-01, 3.87514278091038833e-01, 3.77925972215862271e-01,
		3.68708997487613543e-01, 3.59843450851215829e-01, 3.51310880606601483e-01, 3.43094149301072793e-01,
		3.35177312361997326e-01, 3.27545510371581250e-01, 3.20184873200665854e-01, 3.13082434482556182e-01,
		3.06226055127975738e-01, 2.99604354767027625e-01, 2.93206650159908988e-01, 2.87022899748871851e-01,
		2.81043653635944191e-01, 2.75260008365130482e-01, 2.69663565968592922e-01, 2.64246396805493722e-01,
		2.59001005781242910e-01, 2.53920301585792152e-01, 2.48997568633569616e-01, 2.44226441425652752e-01,
		2.39600881087469908e-01, 2.35115153864130427e-01, 2.30763811380187006e-01, 2.26541672492370061e-01,
		2.22443806582916848e-01, 2.18465518157651667e-01, 2.14602332627510634e-01, 2.10849983165356192e-01,
		2.07204398540939916e-01, 2.03661691846944048e-01, 2.00218150038134451e-01, 1.96870224213184369e-01,
		1.93614520575835614e-01, 1.90447792018342332e-01, 1.87366930275524757e-01, 1.84368958602731337e-01,
		1.81451024935457061e-01, 1.78610395492258517e-01, 1.75844448786063728e-01, 1.73150670012326841e-01,
		1.70526645785132130e-01, 1.67970059194969018e-01, 1.65478685164280659e-01, 1.63050386078872789e-01,
		1.60683107675126668e-01, 1.58374875164782741e-01, 1.56123789580483313e-01, 1.53928024326647012e-01,
		1.51785821921613967e-01, 1.49695490918038104e-01, 1.47655402989595230e-01, 1.45663990172970714e-01,
		1.43719742255064759e-01, 1.41821204296018161e-01, 1.39966974279406492e-01, 1.38155700881651272e-01,
		1.36386081353280036e-01, 1.34656859505147358e-01, 1.32966823793335631e-01, 1.31314805496822951e-01,
		1.29699676982467121e-01, 1.28120350052274373e-01, 1.26575774368151456e-01, 1.25064935949913525e-01,
		1.23586855742028531e-01, 1.22140588246809095e-01, 1.20725220214797091e-01, 1.19339869410269847e-01,
		1.17983683369542569e-01, 1.16655838444697929e-01, 1.15355538027138341e-01, 1.14082014064304196e-01,
		1.12834516506675933e-01, 1.11612348008638756e-01, 1.10414729938505748e-01, 1.09241298140229107e-01
	};
	static double c[92] = {
		-9.34324982101620849e-02, -8.88655462457056400e-02, -8.42025640710015594e-02, -8.00197329475356850e-02,
		-7.61140695896742742e-02, -7.24979503449798279e-02, -6.91315680305528008e-02, -6.59937548684829400e-02,
		-6.30622960627443691e-02, -6.03186195028546090e-02, -5.77460537415301622e-02, -5.53298900545345917e-02,
		-5.30570267377887678e-02, -5.09157790088607815e-02, -4.88956886418370762e-02, -4.69873701099287749e-02,
		-4.51823771725581441e-02, -4.34730891914191925e-02, -4.18526132547244814e-02, -4.03146998005620635e-02,
		-3.88536695901928741e-02, -3.74643503139678175e-02, -3.61420213951862412e-02, -3.48823657859102590e-02,
		-3.36814277598939601e-02, -3.25355758495872241e-02, -3.14414702215991201e-02, -3.03960338887724092e-02,
		-2.93964272405043761e-02, -2.84400254676326451e-02, -2.75243984977431091e-02, -2.66472931332491295e-02,
		-2.58066171092583355e-02, -2.50004248452490169e-02, -2.42269046769766766e-02, -2.34843674021920808e-02,
		-2.27712359796366053e-02, -2.20860362537580353e-02, -2.14273885856757704e-02, -2.07940002924938278e-02,
		-2.01846588020384680e-02, -1.95982254506131687e-02, -1.90336298507971825e-02, -1.84898647707473392e-02,
		-1.79659814734153059e-02, -1.74610854665435272e-02, -1.69743326215522836e-02, -1.65049256279485614e-02,
		-1.60521107455388889e-02, -1.56151748293941583e-02, -1.51934425987815744e-02, -1.47862741291524755e-02,
		-1.43930625435904746e-02, -1.40132318883947268e-02, -1.36462351735532200e-02, -1.32915525638158481e-02,
		-1.29486897081312058e-02, -1.26171761934997899e-02, -1.22965641133836890e-02, -1.19864267406951872e-02,
		-1.16863572967661634e-02, -1.13959678066728187e-02, -1.11148880363215272e-02, -1.08427645020414097e-02,
		-1.05792595482891699e-02, -1.03240504874694411e-02, -1.00768287969594007e-02, -9.83729936928581100e-03,
		-9.60517980977360075e-03, -9.38019978069253024e-03, -9.16210038542411738e-03, -8.95063359212771269e-03,
		-8.74556169158521510e-03, -8.54665678974113850e-03, -8.35370032837635598e-03, -8.16648263675044672e-03,
		-7.98480250680756731e-03, -7.80846679512038448e-03, -7.63729004610835815e-03, -7.47109413627102155e-03,
		-7.30970794257910974e-03, -7.15296700961526831e-03, -7.00071331050457386e-03, -6.85279473476791898e-03,
		-6.70906567250490436e-03, -6.56938357594156162e-03, -6.43362059965430465e-03, -6.30161902868694133e-03,
		-6.17335654759581381e-03, -6.04832843277599772e-03, -5.92785226855403573e-03, -5.80646571421250274e-03
	};
	static double d[92] = {
		1.52231732148548141e-02, 1.55432739156802779e-02, 1.39427704115529256e-02, 1.30188778595380535e-02,
		1.20537308156481206e-02, 1.12212743814234135e-02, 1.04593772068995155e-02, 9.77152935246192872e-03,
		9.14558853296590195e-03, 8.57521920441479263e-03, 8.05387895665191783e-03, 7.57621105581938320e-03,
		7.13749242975999110e-03, 6.73363455674563707e-03, 6.36106177302769339e-03, 6.01664312456877577e-03,
		5.69762660379651183e-03, 5.40158645564904442e-03, 5.12637818054137179e-03, 4.87010070123063132e-03,
		4.63106425408353530e-03, 4.40776306260523814e-03, 4.19885203091994313e-03, 4.00312675338765356e-03,
		3.81950636768913941e-03, 3.64701875996034349e-03, 3.48478777608903336e-03, 3.33202216089343488e-03,
		3.18800590957243933e-03, 3.05208989963179746e-03, 2.92368454831327604e-03, 2.80225341330263191e-03,
		2.68730754669771433e-03, 2.57840056090781001e-03, 2.47512424928199477e-03, 2.37710474185159329e-03,
		2.28399908626188489e-03, 2.19549222694087999e-03, 2.11129431060647988e-03, 2.03113830151787017e-03,
		1.95477783808431504e-03, 1.88198533271996342e-03, 1.81255026683282061e-03, 1.74627765777343497e-03,
		1.68298668957260738e-03, 1.62250948330413397e-03, 1.56468997867907677e-03, 1.50938294136556956e-03,
		1.45645305381577120e-03, 1.40577410204195132e-03, 1.35722823209698923e-03, 1.31070528520667415e-03,
		1.26610218398581624e-03, 1.22332238280502704e-03, 1.18227536579124689e-03, 1.14287618561547104e-03,
		1.10504504877138735e-03, 1.06870693372033065e-03, 1.03379124229500984e-03, 1.00023147976341462e-03,
		9.67964966977814638e-04, 9.36932567837640211e-04, 9.07078447600385431e-04, 8.78349845840801211e-04,
		8.50696869399103234e-04, 8.24072301700124322e-04, 7.98431425578638139e-04, 7.73731865040699603e-04,
		7.49933430270234851e-04, 7.26997984228045478e-04, 7.04889310988004222e-04, 6.83573001808341274e-04,
		6.63016339480245885e-04, 6.43188204549280233e-04, 6.24058972086363479e-04, 6.05600433142925690e-04,
		5.87785705623952454e-04, 5.70589163373411514e-04, 5.53986366124460195e-04, 5.37953978973039872e-04,
		5.22469776546138497e-04, 5.07512330368975668e-04, 4.93061919122183244e-04, 4.79096874210053288e-04,
		4.65606988544477478e-04, 4.52543254290855321e-04, 4.40005236557871476e-04, 4.27541603637093251e-04,
		4.16760382732723241e-04, 4.01587214073209479e-04, 4.04621847805109239e-04, 4.04621847805109239e-04
	};
	// truncate at z=11
	if(z > 11.0)
		z = 11.0;
	// if z is out of range, just return 0.0
	if(z <= 1.0)
		return 0.0;
	// find position in table
	size_t p = static_cast<size_t>((z-1.0)*10.0);
	if(p > 91)
		p = 91;
	double dx = z-(1.0+p*0.1);
	// spline approximation
	return y[p] + dx*(b[p] + dx*(c[p] + dx*d[p]))
		   - log(z-1.0);
}
#endif

using namespace std;

/****************************************************************************
 *    class cost_model                                                      *
 ****************************************************************************/


bool cost_model::create(const ngila_app::args &rargs)
{
	dA = rargs.cost_intersection;
	dB = rargs.cost_linear;
	dC = rargs.cost_logarithmic;
	dF = rargs.cost_intersection_free;
	dG = rargs.cost_linear_free;
	dH = rargs.cost_logarithmic_free;

	if(rargs.cost_matrix.empty())
	{		
		for(size_t i=0;i<sub_matrix_size;++i)
			for(size_t j=0;j<sub_matrix_size;++j)
				mCost[i][j] = (i == j) ? rargs.cost_match : rargs.cost_mismatch;
	}
	else
	{
		if(!parse_matrix(rargs.cost_matrix.c_str(), mCost, rargs.case_insensitivity))
			return CERRORR("parsing of \'" << rargs.cost_matrix.c_str() << "\' failed.");
	}
	return true;
}

/****************************************************************************
 *    class k2p_model                                                       *
 ****************************************************************************/

enum {nA, nC, nG, nT, nN, nSize};
const int nuc_table[] = {
	/*64*/	-1, nA, nN, nC, nN, -1, -1, nG, nN, -1, -1, nN, -1, nN, nN, -1,
	/*80*/	-1, -1, nN, nN, nT, nT, nN,	nN, -1, nN, -1, -1, -1, -1, -1, -1,
	/*96*/	-1, nA, nN, nC, nN, -1, -1, nG,	nN, -1, -1, nN, -1, nN, nN, -1,
	/*112*/	-1, -1, nN, nN, nT, nT, nN,	nN, -1, nN, -1, -1, -1, -1, -1, -1,
	/*128*/
};
const int pupy[] = {1, 0, 1, 0, -1};

bool k2p_model::create(const ngila_app::args &rargs)
{
	if(rargs.branch_length <= 0.0)
		return CERRORR("branch length must be positive.");
	if(rargs.ratio <= 0.0)
		return CERRORR("Ts/Tv ratio must be positive.");
	if(rargs.avgaln <= 0.0)
		return CERRORR("avgaln must be positive.");
	if(rargs.indel_rate <= 0.0)
		return CERRORR("indel rate must be positive.");
	
	double p_ts = 0.25-0.5*exp(-rargs.branch_length*(2.0*rargs.ratio+1.0)/(rargs.ratio+1.0))
			+ 0.25*exp(-2.0*rargs.branch_length/(rargs.ratio+1.0));
	double p_tv = 0.5-0.5*exp(-2.0*rargs.branch_length/(rargs.ratio+1.0));
	double p_match = 1.0-p_ts-p_tv;
	double l_h = -2.0*rargs.indel_rate*rargs.branch_length
		+log(rargs.avgaln)-log(rargs.avgaln+1.0);
	
	double c_ts = -(log(p_ts)+l_h+log(0.25));
	double c_tv = -(log(p_tv)+l_h+log(0.125));
	double c_m  = -(log(p_match)+l_h+log(0.25));
	
	dNucScale = rargs.no_scale ? 0.0 : 0.5*c_m;

	double sub_costs[nSize][nSize];
	for(size_t i = 0;i<nN;++i)
	{
		sub_costs[i][i] = c_m;
		for(size_t j = 0; j < i; ++j)
		{
			sub_costs[i][j] = sub_costs[j][i] = (pupy[i] == pupy[j]) ? c_ts : c_tv;
		}
		sub_costs[nN][i] = sub_costs[i][nN] = -(l_h+log(0.0625)); // All N's are weighted by 0.25
	}
	sub_costs[nN][nN] = -(l_h+log(0.0625)); // All N's are weighted by 0.25
	
	sub_matrix_clear(mCost);
	for(size_t i = 0;i<64;++i)
	{
		int ni = nuc_table[i];
		for(size_t j=0;j<64;++j)
		{
			int nj = nuc_table[j];
			if(ni == -1 || nj == -1)
				continue;
			mCost[i+64][j+64] = sub_costs[ni][nj] - 2.0*dNucScale;
		}
	}
	dEnd = rargs.no_scale ? log(rargs.avgaln+1.0) : 0.0;
	
	return true;
}

template<class T>
struct isambnuc
{
	bool operator()(T n)
	{
		return (nuc_table[n-64] == nN);
	}
};

double k2p_model::offset(const std::string &seqA, const std::string &seqB) const
{
	isambnuc<std::string::value_type> cpred;
	size_t ncount = count_if(seqA.begin(), seqA.end(), cpred);
	ncount += count_if(seqB.begin(), seqB.end(), cpred);

	return dEnd-static_cast<double>(ncount)*log(4.0);
}

/****************************************************************************
 *    class zeta_model                                                      *
 ****************************************************************************/

bool zeta_model::create(const ngila_app::args &rargs) {
	if(!k2p_model::create(rargs))
		return false;
	if(rargs.indel_slope <= 1.0)
		return CERRORR("indel slope must be greater than 1.0");
	
	dA = -(log(0.5)+log(1.0-exp(-2.0*rargs.indel_rate*rargs.branch_length))
		+ log(rargs.avgaln)-log(rargs.avgaln+1.0)
		- log_zeta(rargs.indel_slope));
	dB = -log(0.25) - dNucScale; // All N's are weighted by 0.25
	dC = rargs.indel_slope;

	dF = dH = 0.0;
	//dG = -log(0.25) - dNucScale;
	dG = rargs.no_scale ? -log(0.25) : 0.0;

	return true;
}

/****************************************************************************
 *    class geo_model                                                       *
 ****************************************************************************/

bool geo_model::create(const ngila_app::args &rargs) {
	if(!k2p_model::create(rargs))
		return false;
	if(rargs.indel_mean <= 1.0)
		return CERRORR("indel mean must be greater than 1.0");
	
	dA = -(log(0.5)+log(1.0-exp(-2.0*rargs.indel_rate*rargs.branch_length))
		+ log(rargs.avgaln)-log(rargs.avgaln+1.0)
		- log(rargs.indel_mean-1));
	dB = -(log(0.25)+log(rargs.indel_mean-1.0)-log(rargs.indel_mean)) - dNucScale; // All N's are weighted by 0.25
	dC = 0.0;

	dF = dH = 0.0;
	//dG = -log(0.25) - dNucScale;
	dG = rargs.no_scale ? -log(0.25) : 0.0;

	return true;
}

/****************************************************************************
 *    class aa_model                                                        *
 ****************************************************************************/

bool aa_model::create(const ngila_app::args &rargs) {
	enum {D=0,E=20,U=40};
	static const char AA[] = "ARNDCQEGHILKMFPSTWYV";
	static const char aa[] = "arndcqeghilkmfpstwyv";
	
	static const double data[440] = {
#		include "lgmod.incl"
	};
	if(rargs.branch_length <= 0.0)
		return CERRORR("branch length must be positive.");
	if(rargs.avgaln <= 0.0)
		return CERRORR("avgaln must be positive.");
	if(rargs.indel_rate <= 0.0)
		return CERRORR("indel rate must be positive.");
	
	// skeleton parameters
	double l_h = -2.0*rargs.indel_rate*rargs.branch_length
		+log(rargs.avgaln)-log(rargs.avgaln+1.0);	
	
	
	double el[20], x[20][20], m[20];
	sub_matrix_clear(mCost);
	
	// cost of stationary amino acids
	std::fill(&vAACost[0], &vAACost[128],
		std::numeric_limits<double>::max()/16.0);
	for(int i=0;i<20;++i)
		vAACost[AA[i]] = vAACost[aa[i]] = -2.0*log(data[D+i]);
		
	// exp the eigenvalues	
	for(int i=0;i<20;++i)
		el[i] = exp(rargs.branch_length*data[E+i]);
	// D*U*el
	for(int i=0;i<20;++i) {
		for(int j=0;j<20;++j) {
			x[i][j] = data[U+j+20*i]*el[j]/data[D+i];
		}
	}
	// x*(U^T*D^-1)
	// matches
	for(int i=0;i<20;++i) {
		double scost = 0.0;
		for(int k=0;k<20;++k)
			scost += x[i][k]*data[U+k+20*i]*data[D+i];
		scost = -(log(scost))-l_h-vAACost[AA[i]];
		m[i] = 0.0;
		if(!rargs.no_scale) {
			m[i] = scost+2*vAACost[AA[i]];
			scost = -2*vAACost[AA[i]];
		}
		mCost[AA[i]][AA[i]] =  mCost[AA[i]][aa[i]]
			= mCost[aa[i]][AA[i]] =  mCost[aa[i]][aa[i]]
			= scost;
	}
	// mismatches
	for(int i=0;i<20;++i) {
		for(int j=i+1;j<20;++j) {
			double scost = 0.0;
			for(int k=0;k<20;++k)
				scost += x[i][k]*data[U+k+20*j]*data[D+j];
			scost = -(log(scost))-l_h-vAACost[AA[j]];
			scost -= (m[i]+m[j])/2;
			
			mCost[AA[i]][AA[j]] =  mCost[AA[j]][AA[i]]
				= mCost[AA[i]][aa[j]] =  mCost[AA[j]][aa[i]]
				= mCost[aa[i]][AA[j]] =  mCost[aa[j]][AA[i]]
				= mCost[aa[i]][aa[j]] =  mCost[aa[j]][aa[i]]
				= scost;
		}
	}
	dEnd = rargs.no_scale ? log(rargs.avgaln+1.0) : 0.0;
	
	return true;	
}

double aa_model::offset(const string &seqA, const string &seqB) const {
	double off = 0.0;
	for(string::size_type k=0;k<seqA.size();++k) {
		off += vAACost[seqA[k]];
	}
	for(string::size_type k=0;k<seqB.size();++k) {
		off += vAACost[seqB[k]];
	}
	return dEnd+off;
}

/****************************************************************************
 *    class aazeta_model                                                    *
 ****************************************************************************/

bool aazeta_model::create(const ngila_app::args &rargs) {
	if(!aa_model::create(rargs))
		return false;
	if(rargs.indel_slope <= 1.0)
		return CERRORR("indel slope must be greater than 1.0");
	
	dA = -(log(0.5)+log(1.0-exp(-2.0*rargs.indel_rate*rargs.branch_length))
		+ log(rargs.avgaln)-log(rargs.avgaln+1.0)
		- log_zeta(rargs.indel_slope));
	dB = 0.0;
	dC = rargs.indel_slope;
	dF = dH = 0.0;
	dG = 0.0;

	return true;
}

/****************************************************************************
 *    class aageo_model                                                     *
 ****************************************************************************/

bool aageo_model::create(const ngila_app::args &rargs) {
	if(!aa_model::create(rargs))
		return false;
	if(rargs.indel_mean <= 1.0)
		return CERRORR("indel mean must be greater than 1.0");
	
	dA = -(log(0.5)+log(1.0-exp(-2.0*rargs.indel_rate*rargs.branch_length))
		+ log(rargs.avgaln)-log(rargs.avgaln+1.0)
		- log(rargs.indel_mean-1.0));
	dB = -(log(rargs.indel_mean-1.0)-log(rargs.indel_mean));
	dC = 0.0;
	dF = dH = 0.0;
	dG = 0.0;

	return true;
}



