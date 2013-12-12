#ifndef TkDetLayers_TOBLayer_h
#define TkDetLayers_TOBLayer_h


#include "TrackingTools/DetLayers/interface/RodBarrelLayer.h"
#include "TOBRod.h"
#include "Utilities/BinningTools/interface/PeriodicBinFinderInPhi.h"
#include "SubLayerCrossings.h"

/** A concrete implementation for TOB layer 
 *  built out of TOBRods
 */

#pragma GCC visibility push(hidden)
class TOBLayer GCC11_FINAL : public RodBarrelLayer, public GeometricSearchDetWithGroups{
 public:
  typedef PeriodicBinFinderInPhi<double>   BinFinderType;


  TOBLayer(std::vector<const TOBRod*>& innerRods,
	   std::vector<const TOBRod*>& outerRods)  __attribute__ ((cold));
  ~TOBLayer()  __attribute__ ((cold));
  
  // GeometricSearchDet interface
  
  virtual const std::vector<const GeomDet*>& basicComponents() const {return theBasicComps;}

  virtual const std::vector<const GeometricSearchDet*>& components() const __attribute__ ((cold)) {return theComps;}

  void groupedCompatibleDetsV( const TrajectoryStateOnSurface& tsos,
			       const Propagator& prop,
			       const MeasurementEstimator& est,
			       std::vector<DetGroup> & result) const __attribute__ ((hot));


  // DetLayer interface
  virtual SubDetector subDetector() const {return GeomDetEnumerators::TOB;}
 

 private:
  // private methods for the implementation of groupedCompatibleDets()

  SubLayerCrossings computeCrossings( const TrajectoryStateOnSurface& tsos,
				      PropagationDirection propDir) const __attribute__ ((hot));
  
  bool addClosest( const TrajectoryStateOnSurface& tsos,
		   const Propagator& prop,
		   const MeasurementEstimator& est,
		   const SubLayerCrossing& crossing,
		   std::vector<DetGroup>& result) const __attribute__ ((hot));

  float computeWindowSize( const GeomDet* det, 
			   const TrajectoryStateOnSurface& tsos, 
			   const MeasurementEstimator& est) const __attribute__ ((hot));
  
  double calculatePhiWindow( double Xmax, const GeomDet& det,
			     const TrajectoryStateOnSurface& state) const __attribute__ ((hot));

  bool overlap( const GlobalPoint& gpos, const GeometricSearchDet& rod, float phiWin) const  __attribute__ ((hot));


  void searchNeighbors( const TrajectoryStateOnSurface& tsos,
			const Propagator& prop,
			const MeasurementEstimator& est,
			const SubLayerCrossing& crossing,
			float window, 
			std::vector<DetGroup>& result,
			bool checkClosest) const __attribute__ ((hot));

  const std::vector<const GeometricSearchDet*>& subLayer( int ind) const {
    return (ind==0 ? theInnerComps : theOuterComps);}
  
  BoundCylinder* cylinder( const std::vector<const GeometricSearchDet*>& rods) const __attribute__ ((cold));


 private:
  std::vector<const GeometricSearchDet*> theComps;
  std::vector<const GeometricSearchDet*> theInnerComps;
  std::vector<const GeometricSearchDet*> theOuterComps;
  std::vector<const GeomDet*> theBasicComps;
  
  BinFinderType    theInnerBinFinder;
  BinFinderType    theOuterBinFinder;

  ReferenceCountingPointer<BoundCylinder>  theInnerCylinder;
  ReferenceCountingPointer<BoundCylinder>  theOuterCylinder;
    
};


#pragma GCC visibility pop
#endif 
