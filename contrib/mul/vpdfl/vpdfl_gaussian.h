#ifndef vpdfl_gaussian_h
#define vpdfl_gaussian_h
#ifdef __GNUC__
#pragma interface
#endif

//:
// \file
// \author Tim Cootes
// \date 16-Oct-98
// \brief Multi-variate gaussian PDF with arbitrary axes.
// \verbatim
//    IMS   Converted to VXL 18 April 2000
// \endverbatim


#include <vpdfl/vpdfl_pdf_base.h>
#include <vnl/io/vnl_io_matrix.h>



//: Class for multi-variate gaussians with arbitrary axes.
//  Covariance matrix is represented by its eigenvectors and values
class vpdfl_gaussian : public vpdfl_pdf_base {
private:
	vnl_matrix<double> evecs_;
	vnl_vector<double> evals_;
	double log_k_;
	void calcLogK();
  //: Workspace
  // The difference between an input vector an the mean
  mutable vnl_vector<double> dx_;
  //: Workspace
  // Usually the input vector after normalisation.
  mutable vnl_vector<double> b_;

	
public:

		//: Dflt ctor
	vpdfl_gaussian();

		//: Destructor
	virtual ~vpdfl_gaussian();
	
		//: Initialise
		// WARNING - the error checking for inconsistent parameters is not
    // foolproof.
	void set(const vnl_vector<double>& mean, 
			 const vnl_vector<double>& variance,
			 const vnl_matrix<double>& evecs,
			 const vnl_vector<double>& evals);

		//: Initialise safely
		// Calculates the variance, and checks that
		// the Eigenvalues are ordered and the Eigenvectors are unit normal
		// Turn off assertions to remove error checking.
	virtual void set(const vnl_vector<double>& mean, 
			 const vnl_matrix<double>& evecs,
			 const vnl_vector<double>& evals);
			
		//: Initialise from mean and covariance matrix
		//  Note, eigenvectors computed from covar, and those corresponding
		//  to evals smaller than min_eval are truncated
	void set(const vnl_vector<double>& mean,
			 const vnl_matrix<double>& covar,
			 double min_eval = 1e-6);
			
			 	
		//: Eigenvectors of covariance matrix
		// List ordering corresponds to eVals();
	const vnl_matrix<double>& eigenvecs() const { return evecs_; }
	
		//: Eigenvalues of covariance matrix
		// The list is ordered - largest Eigenvalues first.
	const vnl_vector<double>& eigenvals() const { return evals_; }

		//: The Covariance matrix of the Gaussian.
		// This value is calculated on the fly each time so calling this function
		// may not be very efficient
	vnl_matrix<double> covariance() const;

		//: log of normalisation constant for gaussian 
	double log_k() const { return log_k_; }

    //: Create a sampler object on the heap
    // Caller is responsible for deletion.
  virtual vpdfl_sampler_base* new_sampler() const;

		//: Log of probability density at x
		// This value is also the Normalised Mahalanobis distance
		// from the centroid to the given vector.
  virtual double log_p(const vnl_vector<double>& x) const;
	
		//: Gradient of PDF at x
	virtual void gradient(vnl_vector<double>& g, 
								        const vnl_vector<double>& x,
                        double& p) const;
	

		//: Compute threshold for PDF to pass a given proportion
	virtual double log_prob_thresh(double pass_proportion) const;
	
		//: Compute nearest point to x which has a density above a threshold
		// \param x This will be modified to the nearest plausible position.
    // 
    // \param log_p_min. This describes the boundary of the plausible region.
    // Anywhere with a log probability density smaller than this is outside
    // the region.
	virtual void nearest_plausible(vnl_vector<double>& x, double log_p_min) const;


	/*========= methods which do not change state (const) ==========*/

		//: Version number for I/O 
	short version_no() const;

		//: Name of the class
	virtual vcl_string is_a() const;

		//: Create a copy on the heap and return base class pointer
	virtual	vpdfl_pdf_base*	clone()	const;

		//: Print class to os
	virtual void print_summary(vcl_ostream& os) const;

		
		//: Save class to binary file stream
		//!in: bfs: Target binary file stream
	virtual void b_write(vsl_b_ostream& bfs) const;

	/*========== methods which change state (non-const) ============*/

		//: Load class from binary file stream
		//!out: bfs: Target binary file stream
	virtual void b_read(vsl_b_istream& bfs);

protected:

private:

		//: To record name of class, returned by is_a() method
	static vcl_string class_name_;

};

#endif // vpdfl_gaussian_h
//==================< end of vpdfl_gaussian.h >====================


