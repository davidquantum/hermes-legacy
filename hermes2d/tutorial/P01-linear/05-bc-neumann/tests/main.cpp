#define HERMES_REPORT_ALL
#include "hermes2d.h"

// This test makes sure that example 05-bc-neumann works correctly. 

const bool HERMES_VISUALIZATION = true;           // Set to "false" to suppress Hermes OpenGL visualization. 
const bool VTK_VISUALIZATION = true;              // Set to "true" to enable VTK output.
const int P_INIT = 5;                             // Uniform polynomial degree of mesh elements.
const int INIT_REF_NUM = 0;                       // Number of initial uniform mesh refinements.
MatrixSolverType matrix_solver = SOLVER_UMFPACK;  // Possibilities: SOLVER_AMESOS, SOLVER_AZTECOO, SOLVER_MUMPS,
                                                  // SOLVER_PETSC, SOLVER_SUPERLU, SOLVER_UMFPACK.

// Problem parameters.
const double LAMBDA_AL = 236.0;            // Thermal cond. of Al for temperatures around 20 deg Celsius.
const double LAMBDA_CU = 386.0;            // Thermal cond. of Cu for temperatures around 20 deg Celsius.
const double VOLUME_HEAT_SRC = 3e3;        // Volume heat sources generated by electric current.        
const double HEAT_FLUX = 0.0;              // Heat flux through the "Outer" part of the boundary. 
const double BDY_A_PARAM = 1.0;
const double BDY_B_PARAM = 2.0;
const double BDY_C_PARAM = 20.0;

// Weak forms.
#include "../definitions.cpp"

int main(int argc, char* argv[])
{
  // Instantiate a class with global functions.
  Hermes2D hermes2d;

  // Load the mesh.
  Mesh mesh;
  H2DReader mloader;
  mloader.load("../domain.mesh", &mesh);

  // Perform initial mesh refinements (optional).
  for (int i=0; i < INIT_REF_NUM; i++) mesh.refine_all_elements();

  // Initialize the weak formulation.
  CustomWeakFormPoissonNeumann wf("Aluminum", LAMBDA_AL, "Copper", LAMBDA_CU, VOLUME_HEAT_SRC,
                                  "Outer", HEAT_FLUX);
  
  // Initialize boundary conditions.
  CustomDirichletCondition bc_essential(Hermes::vector<std::string>("Bottom", "Inner", "Left"),
                                        BDY_A_PARAM, BDY_B_PARAM, BDY_C_PARAM);
  EssentialBCs bcs(&bc_essential);

  // Create an H1 space with default shapeset.
  H1Space space(&mesh, &bcs, P_INIT);

  // Testing n_dof and correctness of solution vector
  // for p_init = 1, 2, ..., 10
  int success = 1;
  Solution sln;
  for (int p_init = 1; p_init <= 10; p_init++) {

    printf("********* p_init = %d *********\n", p_init);
    space.set_uniform_order(p_init);
    int ndof = space.get_num_dofs();
    info("ndof = %d", ndof);

    // Initialize the FE problem.
    DiscreteProblem dp(&wf, &space);

    // Set up the solver, matrix, and rhs according to the solver selection.
    SparseMatrix* matrix = create_matrix(matrix_solver);
    Vector* rhs = create_vector(matrix_solver);
    Solver* solver = create_linear_solver(matrix_solver, matrix, rhs);

    // Initialize the solution.
    Solution sln;

    // Initial coefficient vector for the Newton's method.  
    scalar* coeff_vec = new scalar[ndof];
    memset(coeff_vec, 0, ndof*sizeof(scalar));

    // Perform Newton's iteration.
    if (!hermes2d.solve_newton(coeff_vec, &dp, solver, matrix, rhs)) error("Newton's iteration failed.");

    // Translate the resulting coefficient vector into the Solution sln.
    Solution::vector_to_solution(coeff_vec, &space, &sln);

    double sum = 0;
    for (int i=0; i < ndof; i++) sum += coeff_vec[i];
    printf("coefficient sum = %g\n", sum);

    // Actual test. The values of 'sum' depend on the
    // current shapeset. If you change the shapeset,
    // you need to correct these numbers.
    if (p_init == 1 && fabs(sum - 73.2675) > 1e-3) success = 0;
    if (p_init == 2 && fabs(sum - 65.432) > 1e-3) success = 0;
    if (p_init == 3 && fabs(sum - 67.6476) > 1e-3) success = 0;
    if (p_init == 4 && fabs(sum - 65.6321) > 1e-3) success = 0;
    if (p_init == 5 && fabs(sum - 67.7464) > 1e-3) success = 0;
    if (p_init == 6 && fabs(sum - 65.4558) > 1e-3) success = 0;
    if (p_init == 7 && fabs(sum - 67.8978) > 1e-3) success = 0;
    if (p_init == 8 && fabs(sum - 65.279) > 1e-3) success = 0;
    if (p_init == 9 && fabs(sum - 68.0776) > 1e-3) success = 0;
    if (p_init == 10 && fabs(sum - 65.0863) > 1e-3) success = 0;

    delete [] coeff_vec;
  }

  if (success == 1) {
    printf("Success!\n");
    return ERR_SUCCESS;
  }
  else {
    printf("Failure!\n");
    return ERR_FAILURE;
  }
}
